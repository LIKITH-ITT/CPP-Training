#include "Application.h"
#include "IConsoleUI.h"
#include "PlaylistManager.h"
#include "PlaylistRepository.h"
#include "SystemAudioPlayer.h"
#include "SongNavigator.h"

int main()
{
    IConsoleUI ui;
    PlaylistManager manager;
    PlaylistRepository repo;
    SystemAudioPlayer player;
    SongNavigator navigator;

    Application app(&ui, &manager, &repo, &player, &navigator);
    return static_cast<int>(app.run());
}
