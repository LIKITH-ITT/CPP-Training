#include "PlaylistRepository.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdio>
#include <dirent.h>

const std::string PlaylistRepository::PLAYLIST_DIR = "resources/playlists/";
const std::string PlaylistRepository::AUDIO_DIR = "resources/audio/";

ErrorCode PlaylistRepository::save(const Playlist& playlist)
{
    ErrorCode errorCode = ErrorCode::SUCCESS;

    std::string path = PLAYLIST_DIR + playlist.name + ".txt";
    std::ofstream file(path.c_str());

    if (!file.is_open())
    {
        errorCode = ErrorCode::FILE_WRITE_ERROR;
    }
    else
    {
        file << playlist.name << "\n";

        for (int index = 0; index < playlist.size(); ++index)
        {
            file << formatLine((index + 1), playlist.getSong(index)) << "\n";
        }

        if (!file.good())
        {
            errorCode = ErrorCode::FILE_WRITE_ERROR;
        }
    }

    return errorCode;
}

ErrorCode PlaylistRepository::load(const std::string& name, Playlist& playlist)
{
    ErrorCode errorCode = ErrorCode::SUCCESS;

    std::string path = PLAYLIST_DIR + name + ".txt";
    std::ifstream file(path.c_str());

    if (!file.is_open())
    {
        errorCode = ErrorCode::FILE_NOT_FOUND;
    }
    else
    {
        std::string line;

        if (!std::getline(file, line))
        {
            errorCode = ErrorCode::FILE_READ_ERROR;
        }
        else
        {
            playlist.name = line;
            playlist.songs.clear();

            std::vector<std::pair<int, Song>> indexedSongs;

            while (std::getline(file, line))
            {
                if (line.empty())
                    continue;

                int index = 0;
                Song song;

                if (!parseLine(line, index, song))
                {
                    errorCode = ErrorCode::FILE_READ_ERROR;
                    break;
                }

                indexedSongs.push_back(std::make_pair(index, song));
            }

            if (errorCode == ErrorCode::SUCCESS)
            {
                std::sort(indexedSongs.begin(), indexedSongs.end(), comparePairs);

                for (int index = 0; index < indexedSongs.size(); ++index)
                {
                    playlist.songs.push_back(indexedSongs[index].second);
                }
            }
        }
    }

    return errorCode;
}

ErrorCode PlaylistRepository::remove(const std::string& name)
{
    ErrorCode errorCode = ErrorCode::SUCCESS;

    std::string path = PLAYLIST_DIR + name + ".txt";

    if (std::remove(path.c_str()) != 0)
    {
        errorCode = ErrorCode::FILE_NOT_FOUND;
    }

    return errorCode;
}

std::vector<std::string> PlaylistRepository::listSaved()
{
    std::vector<std::string> result = scanDirectory(PLAYLIST_DIR, ".txt", true);
    return result;
}

std::vector<std::string> PlaylistRepository::listAudioFiles()
{
    std::vector<std::string> result = scanDirectory(AUDIO_DIR, ".wav", false);
    return result;
}

std::string PlaylistRepository::formatLine(int index, const Song& song) const
{
    std::ostringstream oss;
    oss << index << ","
        << song.title << ","
        << song.artist << ","
        << song.duration << ","
        << song.filePath;

    std::string result = oss.str();
    return result;
}

bool PlaylistRepository::parseLine(const std::string& line, int& playlistIndex, Song& playlistSong) const
{
    bool isParsed = true;

    std::istringstream iss(line);
    std::string token;

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

std::vector<std::string> PlaylistRepository::scanDirectory(const std::string& dirPath, const std::string& extension, bool stripExtension) const
{
    std::vector<std::string> results;

    DIR* dir = opendir(dirPath.c_str());

    if (dir != NULL)
    {
        struct dirent* entry;

        while ((entry = readdir(dir)) != NULL)
        {
            std::string fname = entry->d_name;

            if (fname == "." || fname == "..")
                continue;

            if (fname.size() <= extension.size())
                continue;

            if (fname.substr(fname.size() - extension.size()) == extension)
            {
                if (stripExtension)
                {
                    results.push_back(
                        fname.substr(0, fname.size() - extension.size()));
                }
                else
                {
                    results.push_back(fname);
                }
            }
        }

        closedir(dir);
        std::sort(results.begin(), results.end());
    }

    return results;
}

bool PlaylistRepository::comparePairs(
    const std::pair<int, Song>& a,
    const std::pair<int, Song>& b)
{
    bool result = (a.first < b.first);
    return result;
}