#ifndef ICONSOLEUI_H
#define ICONSOLEUI_H

#include <string>
#include <vector>
#include "Playlist.h"
#include "Song.h"
#include "ErrorCode.h"
#include "IAudioPlayer.h"

class IConsoleUI
{
public:
    IConsoleUI();
    virtual ~IConsoleUI();

    virtual void showMainMenu() const;
    virtual void showPlaylistMenu(const std::string& playlistName) const;
    virtual void showPlaylist(const Playlist& playlist) const;
    virtual void showPlaybackStatus(int state, const Song* song) const;
    virtual void showAudioFiles(const std::vector<std::string>& files) const;
    virtual void showSavedPlaylists(const std::vector<std::string>& names) const;
    virtual void showMessage(const std::string& msg) const;
    virtual void showError(ErrorCode code) const;

    virtual std::string getInput() const;
    virtual std::string prompt(const std::string& label) const;
};

#endif