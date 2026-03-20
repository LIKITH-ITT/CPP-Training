#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include "IPlaylistManager.h"
#include "IPlaylistRepository.h"
#include "IAudioPlayer.h"
#include "ConsoleUI.h"
#include "SongNavigator.h"
#include "ErrorCode.h"

class Application
{
public:
    Application(ConsoleUI* ui, IPlaylistManager* manager, IPlaylistRepository* repo, IAudioPlayer* player, SongNavigator* navigator);
    ~Application() {}

    ErrorCode run();

private:
    ConsoleUI* ui_;
    IPlaylistManager* manager_;
    IPlaylistRepository* repo_;
    IAudioPlayer* player_;
    SongNavigator* navigator_;
    std::string activePlaylistName_;

    ErrorCode handleCreatePlaylist();
    ErrorCode handleOpenPlaylist();
    ErrorCode handleDeletePlaylist();

    ErrorCode handleAddSong();
    ErrorCode handleRemoveSong();
    ErrorCode handleMoveSongUp();
    ErrorCode handleMoveSongDown();
    ErrorCode handleDisplaySongs();
    ErrorCode handleSavePlaylist();

    ErrorCode handlePlay();
    ErrorCode handlePause();
    ErrorCode handleStop();
    ErrorCode handleNext();
    ErrorCode handlePrev();

    bool isValidPlaylistOpen() const;
    int parseIntInput(const std::string& input, bool& valid) const;
    std::string runPlaylistMenu();
};

#endif
