#include <gtest/gtest.h>
#include "Playlist.h"
#include "Song.h"
#include "ErrorCode.h"

class GivenAnEmptyPlaylist : public ::testing::Test
{
protected:
    Playlist playlist;
    Song song1;
    Song song2;
    Song song3;

    void SetUp() override
    {
        playlist = Playlist("rock");
        song1 = Song("Numb", "Linkin Park", 185,"resources/audio/numb.wav");
        song2 = Song("Believer", "Imagine Dragons", 204,"resources/audio/believer.wav");
        song3 = Song("Radioactive", "Imagine Dragons", 186,"resources/audio/radioactive.wav");
    }
};

class GivenAPlaylistWithOneSong : public ::testing::Test
{
protected:
    Playlist playlist;
    Song song1;
    Song song2;

    void SetUp() override
    {
        playlist = Playlist("rock");
        song1 = Song("Numb", "Linkin Park", 185,"resources/audio/numb.wav");
        song2 = Song("Believer", "Imagine Dragons", 204,"resources/audio/believer.wav");
        playlist.addSong(song1);
    }
};

class GivenAPlaylistWithThreeSongs : public ::testing::Test
{
protected:
    Playlist playlist;
    Song song1;
    Song song2;
    Song song3;

    void SetUp() override
    {
        playlist = Playlist("rock");
        song1 = Song("Numb", "Linkin Park", 185,"resources/audio/numb.wav");
        song2 = Song("Believer", "Imagine Dragons", 204,"resources/audio/believer.wav");
        song3 = Song("Radioactive", "Imagine Dragons", 186,"resources/audio/radioactive.wav");
        playlist.addSong(song1);
        playlist.addSong(song2);
        playlist.addSong(song3);
    }
};

TEST_F(GivenAnEmptyPlaylist, WhenDefaultConstructed_ThenNameIsEmptyAndPlaylistIsEmpty)
{
    Playlist p;
    EXPECT_EQ(p.name, "");
    EXPECT_TRUE(p.isEmpty());
    EXPECT_EQ(p.size(), 0u);
}

TEST_F(GivenAnEmptyPlaylist, WhenConstructedWithName_ThenNameIsSetAndPlaylistIsEmpty)
{
    EXPECT_EQ(playlist.name, "rock");
    EXPECT_TRUE(playlist.isEmpty());
}

TEST_F(GivenAnEmptyPlaylist, WhenAddSongCalled_ThenReturnsSuccess)
{
    EXPECT_EQ(playlist.addSong(song1), ErrorCode::SUCCESS);
}

TEST_F(GivenAnEmptyPlaylist, WhenAddSongCalled_ThenSizeIncreasesToOne)
{
    playlist.addSong(song1);
    EXPECT_EQ(playlist.size(), 1u);
}

TEST_F(GivenAnEmptyPlaylist, WhenAddSongCalled_ThenPlaylistIsNoLongerEmpty)
{
    playlist.addSong(song1);
    EXPECT_FALSE(playlist.isEmpty());
}

TEST_F(GivenAnEmptyPlaylist, WhenMultipleSongsAdded_ThenInsertionOrderIsPreserved)
{
    playlist.addSong(song1);
    playlist.addSong(song2);
    playlist.addSong(song3);
    EXPECT_EQ(playlist.getSong(0).title, "Numb");
    EXPECT_EQ(playlist.getSong(1).title, "Believer");
    EXPECT_EQ(playlist.getSong(2).title, "Radioactive");
}

TEST_F(GivenAPlaylistWithOneSong, WhenRemoveSongCalledWithValidIndex_ThenReturnsSuccess)
{
    EXPECT_EQ(playlist.removeSong(0), ErrorCode::SUCCESS);
}

TEST_F(GivenAPlaylistWithOneSong, WhenRemoveSongCalledWithValidIndex_ThenPlaylistBecomesEmpty)
{
    playlist.removeSong(0);
    EXPECT_TRUE(playlist.isEmpty());
}

TEST_F(GivenAPlaylistWithThreeSongs, WhenRemoveSongCalledWithFirstIndex_ThenSecondSongBecomesFirst)
{
    playlist.removeSong(0);
    EXPECT_EQ(playlist.getSong(0).title, "Believer");
}

TEST_F(GivenAPlaylistWithThreeSongs, WhenRemoveSongCalledWithMiddleIndex_ThenSizeDecreasesByOne)
{
    playlist.removeSong(1);
    EXPECT_EQ(playlist.size(), 2u);
}

TEST_F(GivenAnEmptyPlaylist, WhenRemoveSongCalledOnEmptyPlaylist_ThenReturnsInvalidIndex)
{
    EXPECT_EQ(playlist.removeSong(0), ErrorCode::INVALID_INDEX);
}

TEST_F(GivenAPlaylistWithOneSong, WhenRemoveSongCalledWithNegativeIndex_ThenReturnsInvalidIndex)
{
    EXPECT_EQ(playlist.removeSong(-1), ErrorCode::INVALID_INDEX);
}

TEST_F(GivenAPlaylistWithOneSong, WhenRemoveSongCalledWithOutOfBoundsIndex_ThenReturnsInvalidIndex)
{
    EXPECT_EQ(playlist.removeSong(99), ErrorCode::INVALID_INDEX);
}

TEST_F(GivenAPlaylistWithThreeSongs, WhenMoveSongUpCalledWithValidIndex_ThenReturnsSuccess)
{
    EXPECT_EQ(playlist.moveSongUp(1), ErrorCode::SUCCESS);
}

TEST_F(GivenAPlaylistWithThreeSongs, WhenMoveSongUpCalledWithIndex1_ThenFirstAndSecondSongsAreSwapped)
{
    playlist.moveSongUp(1);
    EXPECT_EQ(playlist.getSong(0).title, "Believer");
    EXPECT_EQ(playlist.getSong(1).title, "Numb");
}

TEST_F(GivenAPlaylistWithThreeSongs, WhenMoveSongUpCalledWithFirstIndex_ThenReturnsInvalidIndex)
{
    EXPECT_EQ(playlist.moveSongUp(0), ErrorCode::INVALID_INDEX);
}

TEST_F(GivenAPlaylistWithThreeSongs, WhenMoveSongUpCalledWithNegativeIndex_ThenReturnsInvalidIndex)
{
    EXPECT_EQ(playlist.moveSongUp(-1), ErrorCode::INVALID_INDEX);
}

TEST_F(GivenAPlaylistWithThreeSongs, WhenMoveSongUpCalledWithOutOfBoundsIndex_ThenReturnsInvalidIndex)
{
    EXPECT_EQ(playlist.moveSongUp(99), ErrorCode::INVALID_INDEX);
}

TEST_F(GivenAPlaylistWithThreeSongs, WhenMoveSongDownCalledWithValidIndex_ThenReturnsSuccess)
{
    EXPECT_EQ(playlist.moveSongDown(0), ErrorCode::SUCCESS);
}

TEST_F(GivenAPlaylistWithThreeSongs, WhenMoveSongDownCalledWithIndex0_ThenFirstAndSecondSongsAreSwapped)
{
    playlist.moveSongDown(0);
    EXPECT_EQ(playlist.getSong(0).title, "Believer");
    EXPECT_EQ(playlist.getSong(1).title, "Numb");
}

TEST_F(GivenAPlaylistWithThreeSongs, WhenMoveSongDownCalledWithLastIndex_ThenReturnsInvalidIndex)
{
    EXPECT_EQ(playlist.moveSongDown(2), ErrorCode::INVALID_INDEX);
}

TEST_F(GivenAPlaylistWithThreeSongs, WhenMoveSongDownCalledWithNegativeIndex_ThenReturnsInvalidIndex)
{
    EXPECT_EQ(playlist.moveSongDown(-1), ErrorCode::INVALID_INDEX);
}

TEST_F(GivenAPlaylistWithThreeSongs, WhenGetSongCalledWithIndex0_ThenFirstSongIsReturned)
{
    EXPECT_EQ(playlist.getSong(0).title, "Numb");
}

TEST_F(GivenAPlaylistWithThreeSongs, WhenGetSongCalledOnConstPlaylist_ThenCorrectSongIsReturned)
{
    const Playlist& constRef = playlist;
    EXPECT_EQ(constRef.getSong(1).title, "Believer");
}

TEST_F(GivenAnEmptyPlaylist, WhenSizeCalledOnEmptyPlaylist_ThenReturnsZero)
{
    EXPECT_EQ(playlist.size(), 0u);
}

TEST_F(GivenAPlaylistWithThreeSongs, WhenSizeCalledAfterAddingThreeSongs_ThenReturnsThree)
{
    EXPECT_EQ(playlist.size(), 3u);
}

TEST_F(GivenAnEmptyPlaylist, WhenIsEmptyCalledOnNewPlaylist_ThenReturnsTrue)
{
    EXPECT_TRUE(playlist.isEmpty());
}

TEST_F(GivenAPlaylistWithOneSong, WhenIsEmptyCalledAfterAddingSong_ThenReturnsFalse)
{
    EXPECT_FALSE(playlist.isEmpty());
}

TEST_F(GivenAPlaylistWithOneSong, WhenIsEmptyCalledAfterRemovingLastSong_ThenReturnsTrue)
{
    playlist.removeSong(0);
    EXPECT_TRUE(playlist.isEmpty());
}
