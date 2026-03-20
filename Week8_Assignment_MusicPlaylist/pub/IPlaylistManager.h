#ifndef IPLAYLISTMANAGER_H
#define IPLAYLISTMANAGER_H

#include <string>
#include <vector>
#include "Playlist.h"
#include "Song.h"
#include "ErrorCode.h"

class IPlaylistManager
{
public:
    virtual ~IPlaylistManager() {}

    virtual ErrorCode createPlaylist(const std::string& name) = 0;
    virtual ErrorCode deletePlaylist(const std::string& name) = 0;
    virtual Playlist& getPlaylist(const std::string& name) = 0;
    virtual std::vector<std::string> listPlaylists() = 0;
    virtual ErrorCode addSong(const std::string& playlistName, const Song& song) = 0;
    virtual ErrorCode removeSong(const std::string& playlistName, int index) = 0;
    virtual ErrorCode moveSongUp(const std::string& playlistName, int index) = 0;
    virtual ErrorCode moveSongDown(const std::string& playlistName, int index) = 0;
};

#endif 