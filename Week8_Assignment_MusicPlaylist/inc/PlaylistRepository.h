#ifndef PLAYLISTREPOSITORY_H
#define PLAYLISTREPOSITORY_H

#include <string>
#include <vector>
#include <utility>
#include "IPlaylistRepository.h"
#include "Playlist.h"
#include "Song.h"
#include "ErrorCode.h"

class PlaylistRepository : public IPlaylistRepository
{
public:
    static const std::string PLAYLIST_DIR;
    static const std::string AUDIO_DIR;

    ErrorCode save(const Playlist& playlist);
    ErrorCode load(const std::string& name, Playlist& out);
    ErrorCode remove(const std::string& name);
    std::vector<std::string> listSaved();
    std::vector<std::string> listAudioFiles();

private:
    std::string formatLine(int index, const Song& song) const;
    bool parseLine(const std::string& line, int& outIndex, Song& outSong) const;
    std::vector<std::string> scanDirectory(const std::string& dirPath, const std::string& ext, bool stripExt) const;
    static bool comparePairs(const std::pair<int, Song>& a, const std::pair<int, Song>& b);
};

#endif
