#include "Application.h"
#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include <cstdlib>

Application::Application(ConsoleUI* ui, IPlaylistManager* manager, IPlaylistRepository* repo, IAudioPlayer* player, SongNavigator* navigator)
    : ui_(ui), manager_(manager), repo_(repo), player_(player), navigator_(navigator), activePlaylistName_("")
{}

ErrorCode Application::run()
{
    while (true)
    {
        ui_->showMainMenu();
        std::string choice = ui_->getInput();

        ErrorCode errorCode = ErrorCode::SUCCESS;

        if  (choice == "1") errorCode = handleCreatePlaylist();
        else if (choice == "2") errorCode = handleOpenPlaylist();
        else if (choice == "3") errorCode = handleDeletePlaylist();
        else if (choice == "4")
        {
            ui_->showMessage("Exiting Music Playlist...!");
            return ErrorCode::SUCCESS;
        }
        else
        {
            errorCode = ErrorCode::INVALID_INPUT;
        }

        if (errorCode != ErrorCode::SUCCESS)
        {
            ui_->showError(errorCode);
        }
    }
}

std::string Application::runPlaylistMenu()
{
    while (true)
    {
        ui_->showPlaylistMenu(activePlaylistName_);
        std::string choice = ui_->getInput();

        ErrorCode errorCode = ErrorCode::SUCCESS;

        if (choice == "1")  errorCode = handleAddSong();
        else if (choice == "2")  errorCode = handleRemoveSong();
        else if (choice == "3")  errorCode = handleMoveSongUp();
        else if (choice == "4")  errorCode = handleMoveSongDown();
        else if (choice == "5")  errorCode = handleDisplaySongs();
        else if (choice == "6")  errorCode = handlePlay();
        else if (choice == "7")  errorCode = handlePause();
        else if (choice == "8")  errorCode = handleStop();
        else if (choice == "9")  errorCode = handleNext();
        else if (choice == "10") errorCode = handlePrev();
        else if (choice == "11") errorCode = handleSavePlaylist();
        else if (choice == "12")
        {
            player_->stop();
            return choice;
        }
        else
        {
            errorCode = ErrorCode::INVALID_INPUT;
        }

        if (errorCode != ErrorCode::SUCCESS)
        {
            ui_->showError(errorCode);
        }
    }
}

ErrorCode Application::handleCreatePlaylist()
{
    std::string name = ui_->prompt("Enter playlist name: ");
    if (name.empty())
    {
        return ErrorCode::INVALID_INPUT;
    }

    ErrorCode errorCode = manager_->createPlaylist(name);
    if (errorCode != ErrorCode::SUCCESS)
    {
        return errorCode;
    }

    ui_->showMessage("Playlist '" + name + "' created successfully.");

    activePlaylistName_ = name;
    navigator_->setPlaylist(&manager_->getPlaylist(activePlaylistName_));

    runPlaylistMenu();
    return ErrorCode::SUCCESS;
}

ErrorCode Application::handleOpenPlaylist()
{
    std::vector<std::string> saved = repo_->listSaved();
    ui_->showSavedPlaylists(saved);

    if (saved.empty())
    {
        return ErrorCode::FILE_NOT_FOUND;
    }

    std::string name = ui_->prompt("Enter playlist name to open: ");
    if (name.empty())
    {
        return ErrorCode::INVALID_INPUT;
    }

    Playlist loaded;
    ErrorCode errorCode = repo_->load(name, loaded);
    if (errorCode != ErrorCode::SUCCESS)
    {
        return errorCode;
    }

    manager_->createPlaylist(loaded.name);
    manager_->getPlaylist(loaded.name) = loaded;

    activePlaylistName_ = name;
    navigator_->setPlaylist(&manager_->getPlaylist(activePlaylistName_));

    ui_->showMessage("Playlist '" + name + "' opened.");
    runPlaylistMenu();
    return ErrorCode::SUCCESS;
}

ErrorCode Application::handleDeletePlaylist()
{
    std::vector<std::string> saved = repo_->listSaved();
    ui_->showSavedPlaylists(saved);

    if (saved.empty())
    {
        return ErrorCode::FILE_NOT_FOUND;
    }

    std::string name = ui_->prompt("Enter playlist name to delete: ");
    if (name.empty())
    {
        return ErrorCode::INVALID_INPUT;
    }

    ErrorCode errorCode = repo_->remove(name);
    if (errorCode != ErrorCode::SUCCESS)
    {
        return errorCode;
    }

    manager_->deletePlaylist(name);

    if (activePlaylistName_ == name)
    {
        activePlaylistName_ = "";
    }

    ui_->showMessage("Playlist '" + name + "' deleted successfully.");
    return ErrorCode::SUCCESS;
}

ErrorCode Application::handleAddSong()
{
    if (!isValidPlaylistOpen())
    {
        return ErrorCode::PLAYLIST_NOT_FOUND;
    }

    std::vector<std::string> audioFiles = repo_->listAudioFiles();
    ui_->showAudioFiles(audioFiles);

    if (audioFiles.empty())
    {
        return ErrorCode::FILE_NOT_FOUND;
    }

    bool valid = false;
    std::string fileInput = ui_->prompt("Enter file number: ");
    int fileIndex = parseIntInput(fileInput, valid);

    if (!valid || fileIndex < 1 || fileIndex > audioFiles.size())
    {
        return ErrorCode::INVALID_INPUT;
    }

    std::string selectedFile = audioFiles[fileIndex - 1];
    std::string filePath = "resources/audio/" + selectedFile;

    int duration = Song::readDuration(filePath);
    if (duration < 0)
    {
        ui_->showMessage("Warning: Could not read duration. Setting to 0.");
        duration = 0;
    }

    std::string defaultTitle  = Song::stripExtension(selectedFile);
    std::string defaultArtist = "Unknown";

    ui_->showMessage("Press Enter to accept the default shown in [ ]");

    std::string titleInput  = ui_->prompt("Title    [" + defaultTitle  + "]: ");
    std::string artistInput = ui_->prompt("Artist   [" + defaultArtist + "]: ");

    std::string title = titleInput.empty() ? defaultTitle : titleInput;
    std::string artist = artistInput.empty() ? defaultArtist : artistInput;

    Song song(title, artist, duration, filePath);

    ErrorCode errorCode = manager_->addSong(activePlaylistName_, song);
    if (errorCode != ErrorCode::SUCCESS)
    {
        return errorCode;
    }

    navigator_->setPlaylist(&manager_->getPlaylist(activePlaylistName_));

    ui_->showMessage("Song '" + title + "' by '" + artist + "' added." + " Duration: " + Song::formatDuration(duration));
    return ErrorCode::SUCCESS;
}

ErrorCode Application::handleRemoveSong()
{
    if (!isValidPlaylistOpen())
    {
        return ErrorCode::PLAYLIST_NOT_FOUND;
    }

    Playlist& playlist = manager_->getPlaylist(activePlaylistName_);
    if (playlist.isEmpty())
    {
        return ErrorCode::EMPTY_PLAYLIST;
    }

    ui_->showPlaylist(playlist);

    bool valid = false;
    std::string input = ui_->prompt("Enter song number to remove: ");
    int index = parseIntInput(input, valid);

    if (!valid || index < 1 || index > playlist.size())
    {
        return ErrorCode::INVALID_INDEX;
    }

    std::string removedTitle = playlist.getSong(index - 1).title;

    ErrorCode errorCode = manager_->removeSong(activePlaylistName_, index - 1);
    if (errorCode != ErrorCode::SUCCESS)
    {
        return errorCode;
    }

    navigator_->setPlaylist(&manager_->getPlaylist(activePlaylistName_));

    ui_->showMessage("Song '" + removedTitle + "' removed successfully.");
    return ErrorCode::SUCCESS;
}

ErrorCode Application::handleMoveSongUp()
{
    if (!isValidPlaylistOpen())
    {
        return ErrorCode::PLAYLIST_NOT_FOUND;
    }

    Playlist& playlist = manager_->getPlaylist(activePlaylistName_);
    if (playlist.isEmpty())
    {
        return ErrorCode::EMPTY_PLAYLIST;
    }

    ui_->showPlaylist(playlist);

    bool valid = false;
    std::string input = ui_->prompt("Enter song number to move up: ");
    int index = parseIntInput(input, valid);

    if (!valid || index < 1 || index > playlist.size())
    {
        return ErrorCode::INVALID_INDEX;
    }

    ErrorCode errorCode = manager_->moveSongUp(activePlaylistName_, index - 1);
    if (errorCode != ErrorCode::SUCCESS)
    {
        return errorCode;
    }

    ui_->showMessage("Song moved up successfully.");
    ui_->showPlaylist(manager_->getPlaylist(activePlaylistName_));
    return ErrorCode::SUCCESS;
}

ErrorCode Application::handleMoveSongDown()
{
    if (!isValidPlaylistOpen())
    {
        return ErrorCode::PLAYLIST_NOT_FOUND;
    }

    Playlist& playlist = manager_->getPlaylist(activePlaylistName_);
    if (playlist.isEmpty())
    {
        return ErrorCode::EMPTY_PLAYLIST;
    }

    ui_->showPlaylist(playlist);

    bool valid = false;
    std::string input = ui_->prompt("Enter song number to move down: ");
    int index = parseIntInput(input, valid);

    if (!valid || index < 1 || index > playlist.size())
    {
        return ErrorCode::INVALID_INDEX;
    }

    ErrorCode errorCode = manager_->moveSongDown(activePlaylistName_, index - 1);
    if (errorCode != ErrorCode::SUCCESS)
    {
        return errorCode;
    }

    ui_->showMessage("Song moved down successfully.");
    ui_->showPlaylist(manager_->getPlaylist(activePlaylistName_));
    return ErrorCode::SUCCESS;
}

ErrorCode Application::handleDisplaySongs()
{
    if (!isValidPlaylistOpen())
    {
        return ErrorCode::PLAYLIST_NOT_FOUND;
    }

    Playlist& playlist = manager_->getPlaylist(activePlaylistName_);
    ui_->showPlaylist(playlist);

    int state = player_->getState();
    Song* nowPlaying = NULL;
    Song currentSong;

    if (navigator_->hasCurrentSong() && state != IAudioPlayer::STATE_STOPPED)
    {
        currentSong = navigator_->current();
        nowPlaying = &currentSong;
    }

    ui_->showPlaybackStatus(state, nowPlaying);
    return ErrorCode::SUCCESS;
}

ErrorCode Application::handleSavePlaylist()
{
    if (!isValidPlaylistOpen())
    {
        return ErrorCode::PLAYLIST_NOT_FOUND;
    }

    Playlist& playlist = manager_->getPlaylist(activePlaylistName_);
    ErrorCode errorCode = repo_->save(playlist);
    if (errorCode != ErrorCode::SUCCESS)
    {
        return errorCode;
    }

    ui_->showMessage("Playlist '" + activePlaylistName_ + "' saved successfully.");
    return ErrorCode::SUCCESS;
}

ErrorCode Application::handlePlay()
{
    if (!isValidPlaylistOpen())
    {
        return ErrorCode::PLAYLIST_NOT_FOUND;
    }

    Playlist& playlist = manager_->getPlaylist(activePlaylistName_);
    if (playlist.isEmpty())
    {
        return ErrorCode::EMPTY_PLAYLIST;
    }

    if (!navigator_->hasCurrentSong())
    {
        navigator_->setPlaylist(&playlist);
    }

    Song song = navigator_->current();
    int  curState = player_->getState();

    if (curState == IAudioPlayer::STATE_PAUSED)
    {
        ErrorCode errorCode = player_->resume();
        if (errorCode != ErrorCode::SUCCESS)
        {
            return errorCode;
        }
        ui_->showMessage("Resumed: " + song.title + " — " + song.artist);
        return ErrorCode::SUCCESS;
    }

    ErrorCode errorCode = player_->play(song.filePath);
    if (errorCode != ErrorCode::SUCCESS)
    {
        return errorCode;
    }

    ui_->showMessage("Playing: " + song.title + " — " + song.artist + "  [" + Song::formatDuration(song.duration) + "]");
    return ErrorCode::SUCCESS;
}

ErrorCode Application::handlePause()
{
    ErrorCode errorCode = player_->pause();
    if (errorCode != ErrorCode::SUCCESS)
    {
        return errorCode;
    }

    if (navigator_->hasCurrentSong())
    {
        Song song = navigator_->current();
        ui_->showMessage("Paused: " + song.title + " — " + song.artist + "  (press Play to resume)");
    }

    return ErrorCode::SUCCESS;
}

ErrorCode Application::handleStop()
{
    ErrorCode errorCode = player_->stop();
    if (errorCode != ErrorCode::SUCCESS)
    {
        return errorCode;
    }

    ui_->showMessage("Stopped.");
    return ErrorCode::SUCCESS;
}

ErrorCode Application::handleNext()
{
    if (!isValidPlaylistOpen())
    {
        return ErrorCode::PLAYLIST_NOT_FOUND;
    }

    if (manager_->getPlaylist(activePlaylistName_).isEmpty())
    {
        return ErrorCode::EMPTY_PLAYLIST;
    }

    Song next = navigator_->next();
    ErrorCode errorCode = player_->play(next.filePath);
    if (errorCode != ErrorCode::SUCCESS)
    {
        return errorCode;
    }

    ui_->showMessage("Now playing: " + next.title + " — " + next.artist + "  [" + Song::formatDuration(next.duration) + "]");
    return ErrorCode::SUCCESS;
}

ErrorCode Application::handlePrev()
{
    if (!isValidPlaylistOpen())
    {
        return ErrorCode::PLAYLIST_NOT_FOUND;
    }

    if (manager_->getPlaylist(activePlaylistName_).isEmpty())
    {
        return ErrorCode::EMPTY_PLAYLIST;
    }

    Song prev = navigator_->prev();
    ErrorCode errorCode = player_->play(prev.filePath);
    if (errorCode != ErrorCode::SUCCESS)
    {
        return errorCode;
    }

    ui_->showMessage("Now playing: " + prev.title + " — " + prev.artist + "  [" + Song::formatDuration(prev.duration) + "]");
    return ErrorCode::SUCCESS;
}

bool Application::isValidPlaylistOpen() const
{
    return !activePlaylistName_.empty();
}

int Application::parseIntInput(const std::string& input, bool& valid) const
{
    if (input.empty())
    {
        valid = false;
        return -1;
    }
    for (size_t i = 0; i < input.size(); ++i)
    {
        if (!std::isdigit(static_cast<unsigned char>(input[i])))
        {
            valid = false;
            return -1;
        }
    }
    valid = true;
    return std::atoi(input.c_str());
}
