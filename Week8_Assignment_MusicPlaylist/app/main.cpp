#include "Application.h"
#include "ConsoleUI.h"
#include "PlaylistManager.h"
#include "PlaylistRepository.h"
#include "SystemAudioPlayer.h"
#include "SongNavigator.h"

int main()
{
    ConsoleUI ui;
    PlaylistManager manager;
    PlaylistRepository repo;
    SystemAudioPlayer player;
    SongNavigator navigator;

    Application app(&ui, &manager, &repo, &player, &navigator);
    return static_cast<int>(app.run());
}
