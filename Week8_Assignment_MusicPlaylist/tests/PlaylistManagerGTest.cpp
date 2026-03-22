#include <gtest/gtest.h>
#include "PlaylistManager.h"
#include "Playlist.h"
#include "Song.h"
#include "ErrorCode.h"

class GivenAnEmptyPlaylistManager : public ::testing::Test
{
protected:
    PlaylistManager manager;
    Song song1;
    Song song2;

    void SetUp() override
    {
        song1 = Song("berry", "Unknown", 185, "resources/audio/berry.wav");
        song2 = Song("miradar", "Alan Walker", 204, "resources/audio/miradar.wav");
    }
};

class GivenAPlaylistManagerWithOnePlaylist : public ::testing::Test
{
protected:
    PlaylistManager manager;
    Song song1;
    Song song2;

    void SetUp() override
    {
        song1 = Song("berry", "Unknown", 185, "resources/audio/berry.wav");
        song2 = Song("miradar", "Alan Walker", 204, "resources/audio/miradar.wav");
        manager.createPlaylist("rock");
    }
};

class GivenAPlaylistManagerWithSongs : public ::testing::Test
{
protected:
    PlaylistManager manager;
    Song song1;
    Song song2;

    void SetUp() override
    {
        song1 = Song("berry", "Unknown", 185, "resources/audio/berry.wav");
        song2 = Song("miradar", "Alan Walker", 204, "resources/audio/miradar.wav");
        manager.createPlaylist("rock");
        manager.addSong("rock", song1);
        manager.addSong("rock", song2);
    }
};

TEST_F(GivenAnEmptyPlaylistManager, WhenCreatePlaylistCalledWithValidName_ThenReturnsSuccess)
{
    EXPECT_EQ(manager.createPlaylist("rock"), ErrorCode::SUCCESS);
}

TEST_F(GivenAnEmptyPlaylistManager, WhenCreatePlaylistCalledWithEmptyName_ThenReturnsInvalidInput)
{
    EXPECT_EQ(manager.createPlaylist(""), ErrorCode::INVALID_INPUT);
}

TEST_F(GivenAPlaylistManagerWithOnePlaylist, WhenCreatePlaylistCalledWithDuplicateName_ThenReturnsPlaylistAlreadyExists)
{
    EXPECT_EQ(manager.createPlaylist("rock"), ErrorCode::PLAYLIST_ALREADY_EXISTS);
}

TEST_F(GivenAnEmptyPlaylistManager, WhenMultiplePlaylistsCreatedWithUniqueNames_ThenAllReturnSuccess)
{
    EXPECT_EQ(manager.createPlaylist("rock"), ErrorCode::SUCCESS);
    EXPECT_EQ(manager.createPlaylist("chill"), ErrorCode::SUCCESS);
    EXPECT_EQ(manager.createPlaylist("pop"), ErrorCode::SUCCESS);
}

TEST_F(GivenAPlaylistManagerWithOnePlaylist, WhenDeletePlaylistCalledWithExistingName_ThenReturnsSuccess)
{
    EXPECT_EQ(manager.deletePlaylist("rock"), ErrorCode::SUCCESS);
}

TEST_F(GivenAnEmptyPlaylistManager, WhenDeletePlaylistCalledWithNonExistentName_ThenReturnsPlaylistNotFound)
{
    EXPECT_EQ(manager.deletePlaylist("nonexistent"), ErrorCode::PLAYLIST_NOT_FOUND);
}

TEST_F(GivenAPlaylistManagerWithOnePlaylist, WhenDeletePlaylistCalledWithExistingName_ThenPlaylistNoLongerInList)
{
    manager.deletePlaylist("rock");
    EXPECT_TRUE(manager.listPlaylists().empty());
}

TEST_F(GivenAnEmptyPlaylistManager, WhenListPlaylistsCalledWithNoPlaylists_ThenReturnsEmptyVector)
{
    EXPECT_TRUE(manager.listPlaylists().empty());
}

TEST_F(GivenAPlaylistManagerWithOnePlaylist, WhenListPlaylistsCalledWithOnePlaylist_ThenReturnsSizeOfOne)
{
    EXPECT_EQ(manager.listPlaylists().size(), 1u);
}

TEST_F(GivenAnEmptyPlaylistManager, WhenListPlaylistsCalledAfterCreatingThree_ThenReturnsSizeOfThree)
{
    manager.createPlaylist("rock");
    manager.createPlaylist("chill");
    manager.createPlaylist("pop");
    EXPECT_EQ(manager.listPlaylists().size(), 3u);
}

TEST_F(GivenAPlaylistManagerWithOnePlaylist, WhenGetPlaylistCalledWithExistingName_ThenReturnsPlaylistWithCorrectName)
{
    EXPECT_EQ(manager.getPlaylist("rock").name, "rock");
}

TEST_F(GivenAPlaylistManagerWithOnePlaylist, WhenGetPlaylistReturnedByReference_ThenModificationsArePersisted)
{
    manager.getPlaylist("rock").addSong( Song("berry", "Unknown", 185, "resources/audio/berry.wav"));
    EXPECT_EQ(manager.getPlaylist("rock").size(), 1u);
}

TEST_F(GivenAPlaylistManagerWithOnePlaylist, WhenAddSongCalledWithValidPlaylistAndSong_ThenReturnsSuccess)
{
    EXPECT_EQ(manager.addSong("rock", song1), ErrorCode::SUCCESS);
}

TEST_F(GivenAnEmptyPlaylistManager, WhenAddSongCalledWithNonExistentPlaylist_ThenReturnsPlaylistNotFound)
{
    EXPECT_EQ(manager.addSong("nonexistent", song1), ErrorCode::PLAYLIST_NOT_FOUND);
}

TEST_F(GivenAPlaylistManagerWithOnePlaylist, WhenAddSongCalledTwice_ThenPlaylistSizeIsTwo)
{
    manager.addSong("rock", song1);
    manager.addSong("rock", song2);
    EXPECT_EQ(manager.getPlaylist("rock").size(), 2u);
}

TEST_F(GivenAPlaylistManagerWithSongs, WhenRemoveSongCalledWithValidIndex_ThenReturnsSuccess)
{
    EXPECT_EQ(manager.removeSong("rock", 0), ErrorCode::SUCCESS);
}

TEST_F(GivenAnEmptyPlaylistManager, WhenRemoveSongCalledWithNonExistentPlaylist_ThenReturnsPlaylistNotFound)
{
    EXPECT_EQ(manager.removeSong("nonexistent", 0), ErrorCode::PLAYLIST_NOT_FOUND);
}

TEST_F(GivenAPlaylistManagerWithSongs, WhenRemoveSongCalledWithOutOfBoundsIndex_ThenReturnsInvalidIndex)
{
    EXPECT_EQ(manager.removeSong("rock", 99), ErrorCode::INVALID_INDEX);
}

TEST_F(GivenAPlaylistManagerWithSongs, WhenRemoveSongCalledWithValidIndex_ThenPlaylistSizeDecreasesByOne)
{
    manager.removeSong("rock", 0);
    EXPECT_EQ(manager.getPlaylist("rock").size(), 1u);
}

TEST_F(GivenAPlaylistManagerWithSongs, WhenMoveSongUpCalledWithValidIndex_ThenReturnsSuccess)
{
    EXPECT_EQ(manager.moveSongUp("rock", 1), ErrorCode::SUCCESS);
}

TEST_F(GivenAnEmptyPlaylistManager, WhenMoveSongUpCalledWithNonExistentPlaylist_ThenReturnsPlaylistNotFound)
{
    EXPECT_EQ(manager.moveSongUp("nonexistent", 1), ErrorCode::PLAYLIST_NOT_FOUND);
}

TEST_F(GivenAPlaylistManagerWithSongs, WhenMoveSongUpCalledWithFirstIndex_ThenReturnsInvalidIndex)
{
    EXPECT_EQ(manager.moveSongUp("rock", 0), ErrorCode::INVALID_INDEX);
}

TEST_F(GivenAPlaylistManagerWithSongs, WhenMoveSongUpCalledWithValidIndex_ThenSongsAreSwapped)
{
    manager.moveSongUp("rock", 1);
    EXPECT_EQ(manager.getPlaylist("rock").getSong(0).title, "miradar");
    EXPECT_EQ(manager.getPlaylist("rock").getSong(1).title, "berry");
}

TEST_F(GivenAPlaylistManagerWithSongs, WhenMoveSongDownCalledWithValidIndex_ThenReturnsSuccess)
{
    EXPECT_EQ(manager.moveSongDown("rock", 0), ErrorCode::SUCCESS);
}

TEST_F(GivenAnEmptyPlaylistManager, WhenMoveSongDownCalledWithNonExistentPlaylist_ThenReturnsPlaylistNotFound)
{
    EXPECT_EQ(manager.moveSongDown("nonexistent", 0), ErrorCode::PLAYLIST_NOT_FOUND);
}

TEST_F(GivenAPlaylistManagerWithSongs, WhenMoveSongDownCalledWithLastIndex_ThenReturnsInvalidIndex)
{
    EXPECT_EQ(manager.moveSongDown("rock", 1), ErrorCode::INVALID_INDEX);
}

TEST_F(GivenAPlaylistManagerWithSongs, WhenMoveSongDownCalledWithValidIndex_ThenSongsAreSwapped)
{
    manager.moveSongDown("rock", 0);
    EXPECT_EQ(manager.getPlaylist("rock").getSong(0).title, "miradar");
    EXPECT_EQ(manager.getPlaylist("rock").getSong(1).title, "berry");
}