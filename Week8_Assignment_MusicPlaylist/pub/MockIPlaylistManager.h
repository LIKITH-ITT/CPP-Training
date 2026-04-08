#ifndef MOCKIPLAYLISTMANAGER_H
#define MOCKIPLAYLISTMANAGER_H

#include <gmock/gmock.h>
#include "IPlaylistManager.h"
#include "Playlist.h"
#include "Song.h"
#include "ErrorCode.h"

class MockIPlaylistManager : public IPlaylistManager
{
public:
    MOCK_METHOD(ErrorCode, createPlaylist, (const std::string& name), (override));
    MOCK_METHOD(ErrorCode, deletePlaylist, (const std::string& name), (override));
    MOCK_METHOD(Playlist&, getPlaylist, (const std::string& name), (override));
    MOCK_METHOD(std::vector<std::string>, listPlaylists, (), (override));
    MOCK_METHOD(ErrorCode, addSong, (const std::string& playlistName, const Song& song), (override));
    MOCK_METHOD(ErrorCode, removeSong, (const std::string& playlistName, int index), (override));
    MOCK_METHOD(ErrorCode, moveSongUp, (const std::string& playlistName, int index), (override));
    MOCK_METHOD(ErrorCode, moveSongDown, (const std::string& playlistName, int index), (override));
};

#endif