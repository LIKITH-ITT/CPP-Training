#include "IConsoleUI.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

void IConsoleUI::showMainMenu() const
{
    std::cout << "\n=========================================\n";
    std::cout << "       MUSIC PLAYLIST MANAGER\n";
    std::cout << "=========================================\n";
    std::cout << "MAIN MENU\n";
    std::cout << "---------\n";
    std::cout << "1. Create new playlist\n";
    std::cout << "2. Open existing playlist\n";
    std::cout << "3. Delete playlist\n";
    std::cout << "4. Exit\n";
    std::cout << "\nEnter choice: ";
}

void IConsoleUI::showPlaylistMenu(const std::string& playlistName) const
{
    std::cout << "\nPLAYLIST MENU — " << playlistName << "\n";
    std::cout << std::string(40, '-') << "\n";
    std::cout << " 1. Add song\n";
    std::cout << " 2. Remove song\n";
    std::cout << " 3. Move song up\n";
    std::cout << " 4. Move song down\n";
    std::cout << " 5. Display songs\n";
    std::cout << " 6. Play\n";
    std::cout << " 7. Pause\n";
    std::cout << " 8. Stop\n";
    std::cout << " 9. Next song\n";
    std::cout << "10. Previous song\n";
    std::cout << "11. Save playlist\n";
    std::cout << "12. Back to main menu\n";
    std::cout << "\nEnter choice: ";
}

void IConsoleUI::showPlaylist(const Playlist& playlist) const
{
    std::cout << "\nPlaylist: " << playlist.name << "\n";
    std::cout << std::string(63, '-') << "\n";

    if (playlist.isEmpty())
    {
        std::cout << "  (empty)\n";
        std::cout << std::string(63, '-') << "\n";
        return;
    }

    for (int i = 0; i < playlist.size(); ++i)
    {
    const Song& s = playlist.getSong(i);

    std::cout << std::right << std::setw(3) << (i + 1) << ". "
              << std::left
              << std::setw(25) << s.title
              << " | " << std::setw(20) << s.artist
              << " | " << Song::formatDuration(s.duration)
              << "\n";
}
    std::cout << std::string(63, '-') << "\n";
}

void IConsoleUI::showPlaybackStatus(int state, const Song* song) const
{
    std::cout << "\n--- Playback Status ---\n";
    if (state == IAudioPlayer::STATE_PLAYING && song != NULL)
    {
        std::cout << "Status     : PLAYING\n";
        std::cout << "Now Playing: " << song->title
                  << " — " << song->artist
                  << "  [" << Song::formatDuration(song->duration) << "]\n";
    }
    else if (state == IAudioPlayer::STATE_PAUSED && song != NULL)
    {
        std::cout << "Status     : PAUSED\n";
        std::cout << "Paused On  : " << song->title
                  << " — " << song->artist << "\n";
    }
    else
    {
        std::cout << "Status     : STOPPED\n";
        std::cout << "Now Playing: None\n";
    }
    std::cout << "-----------------------\n";
}

void IConsoleUI::showAudioFiles(const std::vector<std::string>& files) const
{
    std::cout << "\nAvailable audio files:\n";
    std::cout << std::string(35, '-') << "\n";
    if (files.empty())
    {
        std::cout << "  No audio files found in resources/audio/\n";
        std::cout << std::string(35, '-') << "\n";
        return;
    }
    for (int i = 0; i < files.size(); ++i)
    {
        std::cout << std::setw(3) << (i + 1) << ". " << files[i] << "\n";
    }
    std::cout << std::string(35, '-') << "\n";
}

void IConsoleUI::showSavedPlaylists(const std::vector<std::string>& names) const
{
    std::cout << "\nSaved playlists:\n";
    std::cout << std::string(35, '-') << "\n";
    if (names.empty())
    {
        std::cout << "  No saved playlists found.\n";
        std::cout << std::string(35, '-') << "\n";
        return;
    }
    for (int i = 0; i < names.size(); ++i)
    {
        std::cout << std::setw(3) << (i + 1) << ". " << names[i] << "\n";
    }
    std::cout << std::string(35, '-') << "\n";
}

void IConsoleUI::showMessage(const std::string& msg) const
{
    std::cout << "\n" << msg << "\n";
}

void IConsoleUI::showError(ErrorCode code) const
{
    std::cout << "\n" << errorToString(code) << "\n";
}

std::string IConsoleUI::getInput() const
{
    std::string input;
    std::getline(std::cin, input);
    return input;
}

std::string IConsoleUI::prompt(const std::string& label) const
{
    std::cout << label;
    return getInput();
}

IConsoleUI::IConsoleUI()  {}
IConsoleUI::~IConsoleUI() {} 
