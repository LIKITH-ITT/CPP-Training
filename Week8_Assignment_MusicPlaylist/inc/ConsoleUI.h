#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <string>
#include <vector>
#include "Playlist.h"
#include "Song.h"
#include "ErrorCode.h"
#include "IAudioPlayer.h"

class ConsoleUI
{
public:
    void showMainMenu() const;
    void showPlaylistMenu(const std::string& playlistName) const;
    void showPlaylist(const Playlist& playlist) const;
    void showPlaybackStatus(int state, const Song* song) const;
    void showAudioFiles(const std::vector<std::string>& files) const;
    void showSavedPlaylists(const std::vector<std::string>& names) const;
    void showMessage(const std::string& msg) const;
    void showError(ErrorCode code) const;

    std::string getInput() const;
    std::string prompt(const std::string& label) const;
};

#endif
