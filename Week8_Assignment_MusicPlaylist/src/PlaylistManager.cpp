#include "PlaylistManager.h"

ErrorCode PlaylistManager::createPlaylist(const std::string& name)
{
    if (name.empty())
    {
        return ErrorCode::INVALID_INPUT;
    }
    if (playlists_.count(name) > 0)
    {
        return ErrorCode::PLAYLIST_ALREADY_EXISTS;
    }
    playlists_[name] = Playlist(name);
    return ErrorCode::SUCCESS;
}

ErrorCode PlaylistManager::deletePlaylist(const std::string& name)
{
    if (playlists_.count(name) == 0)
    {
        return ErrorCode::PLAYLIST_NOT_FOUND;
    }
    playlists_.erase(name);
    return ErrorCode::SUCCESS;
}

Playlist& PlaylistManager::getPlaylist(const std::string& name)
{
    return playlists_[name];
}

std::vector<std::string> PlaylistManager::listPlaylists()
{
    std::vector<std::string> names;
    std::unordered_map<std::string, Playlist>::iterator it;
    for (it = playlists_.begin(); it != playlists_.end(); ++it)
    {
        names.push_back(it->first);
    }
    return names;
}

ErrorCode PlaylistManager::addSong(const std::string& playlistName, const Song& song)
{
    if (playlists_.count(playlistName) == 0)
    {
        return ErrorCode::PLAYLIST_NOT_FOUND;
    }
    return playlists_[playlistName].addSong(song);
}

ErrorCode PlaylistManager::removeSong(const std::string& playlistName, int index)
{
    if (playlists_.count(playlistName) == 0)
    {
        return ErrorCode::PLAYLIST_NOT_FOUND;
    }
    return playlists_[playlistName].removeSong(index);
}

ErrorCode PlaylistManager::moveSongUp(const std::string& playlistName, int index)
{
    if (playlists_.count(playlistName) == 0)
    {
        return ErrorCode::PLAYLIST_NOT_FOUND;
    }
    return playlists_[playlistName].moveSongUp(index);
}

ErrorCode PlaylistManager::moveSongDown(const std::string& playlistName, int index)
{
    if (playlists_.count(playlistName) == 0)
    {
        return ErrorCode::PLAYLIST_NOT_FOUND;
    }
    return playlists_[playlistName].moveSongDown(index);
}
