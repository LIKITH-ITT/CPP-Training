#include <gtest/gtest.h>
#include "SongNavigator.h"
#include "Playlist.h"
#include "Song.h"
#include "ErrorCode.h"

class GivenANavigatorWithNoPlaylist : public ::testing::Test
{
protected:
    SongNavigator navigator;
};

class GivenANavigatorWithEmptyPlaylist : public ::testing::Test
{
protected:
    SongNavigator navigator;
    Playlist playlist;

    void SetUp() override
    {
        playlist = Playlist("rock");
        navigator.setPlaylist(&playlist);
    }
};

class GivenANavigatorWithOneSong : public ::testing::Test
{
protected:
    SongNavigator navigator;
    Playlist playlist;
    Song song1;

    void SetUp() override
    {
        playlist = Playlist("rock");
        song1 = Song("Numb", "Linkin Park", 185, "resources/audio/numb.wav");
        playlist.addSong(song1);
        navigator.setPlaylist(&playlist);
    }
};

class GivenANavigatorWithThreeSongs : public ::testing::Test
{
protected:
    SongNavigator navigator;
    Playlist playlist;
    Song song1;
    Song song2;
    Song song3;

    void SetUp() override
    {
        playlist = Playlist("rock");
        song1 = Song("Numb", "Linkin Park", 185, "resources/audio/numb.wav");
        song2 = Song("Believer", "Imagine Dragons", 204, "resources/audio/believer.wav");
        song3 = Song("Radioactive", "Imagine Dragons", 186, "resources/audio/radioactive.wav");
        playlist.addSong(song1);
        playlist.addSong(song2);
        playlist.addSong(song3);
        navigator.setPlaylist(&playlist);
    }
};

TEST_F(GivenANavigatorWithNoPlaylist, WhenSetPlaylistCalledWithNullptr_ThenReturnsInvalidInput)
{
    EXPECT_EQ(navigator.setPlaylist(NULL), ErrorCode::INVALID_INPUT);
}

TEST_F(GivenANavigatorWithNoPlaylist, WhenSetPlaylistCalledWithEmptyPlaylist_ThenIndexIsMinusOne)
{
    Playlist empty("empty");
    navigator.setPlaylist(&empty);
    EXPECT_EQ(navigator.getCurrentIndex(), -1);
}

TEST_F(GivenANavigatorWithNoPlaylist, WhenSetPlaylistCalledWithNonEmptyPlaylist_ThenIndexIsZero)
{
    Playlist p("rock");
    p.addSong(Song("Numb", "Linkin Park", 185, "resources/audio/numb.wav"));
    navigator.setPlaylist(&p);
    EXPECT_EQ(navigator.getCurrentIndex(), 0);
}

TEST_F(GivenANavigatorWithNoPlaylist, WhenHasCurrentSongCalledBeforeSettingPlaylist_ThenReturnsFalse)
{
    EXPECT_FALSE(navigator.hasCurrentSong());
}

TEST_F(GivenANavigatorWithEmptyPlaylist, WhenHasCurrentSongCalledWithEmptyPlaylist_ThenReturnsFalse)
{
    EXPECT_FALSE(navigator.hasCurrentSong());
}

TEST_F(GivenANavigatorWithOneSong, WhenHasCurrentSongCalledWithSongsPresent_ThenReturnsTrue)
{
    EXPECT_TRUE(navigator.hasCurrentSong());
}

TEST_F(GivenANavigatorWithNoPlaylist, WhenCurrentCalledBeforeSettingPlaylist_ThenReturnsEmptySong)
{
    EXPECT_EQ(navigator.current().title, "");
}

TEST_F(GivenANavigatorWithThreeSongs, WhenCurrentCalledAfterSetPlaylist_ThenReturnsFirstSong)
{
    EXPECT_EQ(navigator.current().title, "Numb");
}

TEST_F(GivenANavigatorWithEmptyPlaylist, WhenNextCalledOnEmptyPlaylist_ThenReturnsEmptySong)
{
    EXPECT_EQ(navigator.next().title, "");
}

TEST_F(GivenANavigatorWithThreeSongs, WhenNextCalledOnce_ThenReturnsSecondSong)
{
    EXPECT_EQ(navigator.next().title, "Believer");
}

TEST_F(GivenANavigatorWithThreeSongs, WhenNextCalledPastLastSong_ThenWrapsAroundToFirstSong)
{
    navigator.next();
    navigator.next();
    EXPECT_EQ(navigator.next().title, "Numb");
}

TEST_F(GivenANavigatorWithOneSong, WhenNextCalledOnSingleSongPlaylist_ThenReturnsSameSong)
{
    EXPECT_EQ(navigator.next().title, "Numb");
}

TEST_F(GivenANavigatorWithThreeSongs, WhenNextCalledSequentially_ThenIndexAdvancesCorrectly)
{
    EXPECT_EQ(navigator.getCurrentIndex(), 0);
    navigator.next();
    EXPECT_EQ(navigator.getCurrentIndex(), 1);
    navigator.next();
    EXPECT_EQ(navigator.getCurrentIndex(), 2);
    navigator.next();
    EXPECT_EQ(navigator.getCurrentIndex(), 0);
}

TEST_F(GivenANavigatorWithEmptyPlaylist, WhenPrevCalledOnEmptyPlaylist_ThenReturnsEmptySong)
{
    EXPECT_EQ(navigator.prev().title, "");
}

TEST_F(GivenANavigatorWithThreeSongs, WhenPrevCalledFromFirstSong_ThenWrapsAroundToLastSong)
{
    EXPECT_EQ(navigator.prev().title, "Radioactive");
}

TEST_F(GivenANavigatorWithThreeSongs, WhenPrevCalledAfterMovingToSecondSong_ThenReturnsFirstSong)
{
    navigator.next();
    EXPECT_EQ(navigator.prev().title, "Numb");
}

TEST_F(GivenANavigatorWithOneSong, WhenPrevCalledOnSingleSongPlaylist_ThenReturnsSameSong)
{
    EXPECT_EQ(navigator.prev().title, "Numb");
}

TEST_F(GivenANavigatorWithThreeSongs, WhenPrevCalledSequentially_ThenIndexDecrementsCircularly)
{
    EXPECT_EQ(navigator.getCurrentIndex(), 0);
    navigator.prev();
    EXPECT_EQ(navigator.getCurrentIndex(), 2);
    navigator.prev();
    EXPECT_EQ(navigator.getCurrentIndex(), 1);
    navigator.prev();
    EXPECT_EQ(navigator.getCurrentIndex(), 0);
}

TEST_F(GivenANavigatorWithNoPlaylist, WhenResetCalledBeforeSettingPlaylist_ThenReturnsInvalidInput)
{
    EXPECT_EQ(navigator.reset(), ErrorCode::INVALID_INPUT);
}

TEST_F(GivenANavigatorWithThreeSongs, WhenResetCalledAfterNavigation_ThenReturnsSuccess)
{
    navigator.next();
    EXPECT_EQ(navigator.reset(), ErrorCode::SUCCESS);
}

TEST_F(GivenANavigatorWithThreeSongs, WhenResetCalledAfterNavigation_ThenIndexReturnsToZero)
{
    navigator.next();
    navigator.next();
    navigator.reset();
    EXPECT_EQ(navigator.getCurrentIndex(), 0);
}

TEST_F(GivenANavigatorWithEmptyPlaylist, WhenResetCalledOnEmptyPlaylist_ThenIndexRemainsMinusOne)
{
    navigator.reset();
    EXPECT_EQ(navigator.getCurrentIndex(), -1);
}