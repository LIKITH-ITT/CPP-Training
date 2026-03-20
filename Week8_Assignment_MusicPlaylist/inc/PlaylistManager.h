#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include <string>
#include <vector>
#include <unordered_map>
#include "IPlaylistManager.h"
#include "Playlist.h"
#include "Song.h"
#include "ErrorCode.h"

class PlaylistManager : public IPlaylistManager
{
    std::unordered_map<std::string, Playlist> playlists_;

public:
    ErrorCode createPlaylist(const std::string& name);
    ErrorCode deletePlaylist(const std::string& name);
    Playlist&  getPlaylist(const std::string& name);
    std::vector<std::string> listPlaylists();
    ErrorCode addSong(const std::string& playlistName, const Song& song);
    ErrorCode removeSong(const std::string& playlistName,int index);
    ErrorCode moveSongUp(const std::string& playlistName,int index);
    ErrorCode moveSongDown(const std::string& playlistName,int index);    
};

#endif 
