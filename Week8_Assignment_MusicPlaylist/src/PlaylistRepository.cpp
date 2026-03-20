#include "PlaylistRepository.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdio>
#include <dirent.h>

const std::string PlaylistRepository::PLAYLIST_DIR = "resources/playlists/";
const std::string PlaylistRepository::AUDIO_DIR    = "resources/audio/";

ErrorCode PlaylistRepository::save(const Playlist& playlist)
{
    std::string   path = PLAYLIST_DIR + playlist.name + ".txt";
    std::ofstream file(path.c_str());

    if (!file.is_open())
    {
        return ErrorCode::FILE_WRITE_ERROR;
    }

    file << playlist.name << "\n";

    for (int index = 0; index < playlist.size(); ++index)
    {
        file << formatLine((index + 1), playlist.getSong((index))) << "\n";
    }

    if (!file.good())
    {
        return ErrorCode::FILE_WRITE_ERROR;
    }

    return ErrorCode::SUCCESS;
}

ErrorCode PlaylistRepository::load(const std::string& name, Playlist& playlist)
{
    std::string path = PLAYLIST_DIR + name + ".txt";
    std::ifstream file(path.c_str());

    if (!file.is_open())
    {
        return ErrorCode::FILE_NOT_FOUND;
    }

    std::string line;

    if (!std::getline(file, line))
    {
        return ErrorCode::FILE_READ_ERROR;
    }
    playlist.name = line;
    playlist.songs.clear();

    std::vector<std::pair<int, Song> > indexedSongs;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        int index = 0;
        Song song;

        if (!parseLine(line, index, song))
        {
            return ErrorCode::FILE_READ_ERROR;
        }

        indexedSongs.push_back(std::make_pair(index, song));
    }

    std::sort(indexedSongs.begin(), indexedSongs.end(), comparePairs);

    for (int i = 0; i < indexedSongs.size(); ++i)
    {
        playlist.songs.push_back(indexedSongs[i].second);
    }

    return ErrorCode::SUCCESS;
}

ErrorCode PlaylistRepository::remove(const std::string& name)
{
    std::string path = PLAYLIST_DIR + name + ".txt";
    if (std::remove(path.c_str()) != 0)
    {
        return ErrorCode::FILE_NOT_FOUND;
    }
    return ErrorCode::SUCCESS;
}

std::vector<std::string> PlaylistRepository::listSaved()
{
    return scanDirectory(PLAYLIST_DIR, ".txt", true);
}

std::vector<std::string> PlaylistRepository::listAudioFiles()
{
    return scanDirectory(AUDIO_DIR, ".wav", false);
}

std::string PlaylistRepository::formatLine(int index, const Song& song) const
{
    std::ostringstream oss;
    oss << index << ","
        << song.title << ","
        << song.artist << ","
        << song.duration << ","
        << song.filePath;
    return oss.str();
}

bool PlaylistRepository::parseLine(const std::string& line, int& playlistIndex, Song& playlistSong) const
{
    std::istringstream iss(line);
    std::string token;
    bool isParsed = true;

    if (!std::getline(iss, token, ',')) 
    isParsed = false;
    playlistIndex = std::atoi(token.c_str());

    if (!std::getline(iss, playlistSong.title, ','))
    isParsed = false; 

    if (!std::getline(iss, playlistSong.artist, ','))
    isParsed = false;

    if (!std::getline(iss, token, ','))
    isParsed = false;
    playlistSong.duration = std::atoi(token.c_str());

    if (!std::getline(iss, playlistSong.filePath))
    isParsed = false;

    return isParsed;
}

std::vector<std::string> PlaylistRepository::scanDirectory( const std::string& dirPath, const std::string& extension, bool stripExtensionension) const
{
    std::vector<std::string> results;

    DIR* dir = opendir(dirPath.c_str());
    if (dir == NULL)
    {
        return results;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL)
    {
        std::string fname = entry->d_name;

        if (fname.size() <= extension.size())
        {
            continue;
        }

        if (fname.substr(fname.size() - extension.size()) == extension)
        {
            if (stripExtensionension)
            {
                results.push_back(fname.substr(0, fname.size() - extension.size()));
            }
            else
            {
                results.push_back(fname);
            }
        }
    }

    closedir(dir);
    std::sort(results.begin(), results.end());
    return results;
}

bool PlaylistRepository::comparePairs(const std::pair<int, Song>& a, const std::pair<int, Song>& b)
{
    return a.first < b.first;
}
