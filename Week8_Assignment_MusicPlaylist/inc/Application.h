#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include "IPlaylistManager.h"
#include "IPlaylistRepository.h"
#include "IAudioPlayer.h"
#include "IConsoleUI.h"
#include "SongNavigator.h"
#include "ErrorCode.h"

class Application
{
public:
    Application(IConsoleUI* ui, IPlaylistManager* manager, IPlaylistRepository* repo, IAudioPlayer* player, SongNavigator* navigator);
    ~Application() {}

    ErrorCode run();

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
    void setActivePlaylistName(const std::string& name);
    const std::string& getActivePlaylistName() const;

private:
    IConsoleUI* ui_;
    IPlaylistManager* manager_;
    IPlaylistRepository* repo_;
    IAudioPlayer* player_;
    SongNavigator* navigator_;
    std::string activePlaylistName_;

    bool isValidPlaylistOpen() const;
    int parseIntInput(const std::string& input, bool& valid) const;
    std::string runPlaylistMenu();
    ErrorCode checkAndAdvance();
};

#endif
