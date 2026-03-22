#ifndef MOCKCONSOLEUI_H
#define MOCKCONSOLEUI_H

#include <gmock/gmock.h>
#include <string>
#include <vector>
#include "IConsoleUI.h"
#include "Playlist.h"
#include "Song.h"
#include "ErrorCode.h"

class MockIConsoleUI : public IConsoleUI
{
public:
    MOCK_METHOD(void, showMainMenu, (), (const, override));
    MOCK_METHOD(void, showPlaylistMenu, (const std::string& playlistName), (const, override));
    MOCK_METHOD(void, showPlaylist, (const Playlist& playlist), (const, override));
    MOCK_METHOD(void, showPlaybackStatus, (int state, const Song* song), (const, override));
    MOCK_METHOD(void, showAudioFiles, (const std::vector<std::string>& files), (const, override));
    MOCK_METHOD(void, showSavedPlaylists, (const std::vector<std::string>& names), (const, override));
    MOCK_METHOD(void, showMessage, (const std::string& msg), (const, override));
    MOCK_METHOD(void, showError, (ErrorCode code), (const, override));
    MOCK_METHOD(std::string, getInput, (), (const, override));
    MOCK_METHOD(std::string, prompt, (const std::string& label), (const, override));
};

#endif