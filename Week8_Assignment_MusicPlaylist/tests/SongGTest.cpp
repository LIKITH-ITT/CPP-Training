#include <gtest/gtest.h>
#include "Song.h"

class GivenASong : public ::testing::Test
{
protected:
    Song songWithAllFields;
    Song defaultSong;

    void SetUp() override
    {
        songWithAllFields = Song("berry","Linkin Park", 185, "resources/audio/berry.wav");
    }
};

TEST_F(GivenASong, WhenDefaultConstructed_ThenAllFieldsAreEmpty)
{
    EXPECT_EQ(defaultSong.title, "");
    EXPECT_EQ(defaultSong.artist, "");
    EXPECT_EQ(defaultSong.duration, 0);
    EXPECT_EQ(defaultSong.filePath, "");
}

TEST_F(GivenASong, WhenConstructedWithFields_ThenAllFieldsAreSetCorrectly)
{
    EXPECT_EQ(songWithAllFields.title, "berry");
    EXPECT_EQ(songWithAllFields.artist, "Linkin Park");
    EXPECT_EQ(songWithAllFields.duration, 185);
    EXPECT_EQ(songWithAllFields.filePath, "resources/audio/berry.wav");
}

TEST_F(GivenASong, WhenOperatorEqualsCalledWithIdenticalSong_ThenReturnsTrue)
{
    Song duplicate("berry", "Linkin Park", 185, "resources/audio/berry.wav");
    EXPECT_TRUE(songWithAllFields == duplicate);
}

TEST_F(GivenASong, WhenOperatorEqualsCalledWithDifferentTitle_ThenReturnsFalse)
{
    Song other("Believer", "Linkin Park", 185, "resources/audio/berry.wav");
    EXPECT_FALSE(songWithAllFields == other);
}

TEST_F(GivenASong, WhenOperatorEqualsCalledWithDifferentArtist_ThenReturnsFalse)
{
    Song other("berry", "Imagine Dragons", 185, "resources/audio/berry.wav");
    EXPECT_FALSE(songWithAllFields == other);
}

TEST_F(GivenASong, WhenOperatorEqualsCalledWithDifferentFilePath_ThenReturnsFalse)
{
    Song other("berry", "Linkin Park", 185, "resources/audio/other.wav");
    EXPECT_FALSE(songWithAllFields == other);
}

TEST_F(GivenASong, WhenOperatorEqualsCalledWithDifferentDurationOnly_ThenReturnsTrue)
{
    Song other("berry", "Linkin Park", 999, "resources/audio/berry.wav");
    EXPECT_TRUE(songWithAllFields == other);
}

TEST_F(GivenASong, WhenOperatorNotEqualsCalledWithDifferentSong_ThenReturnsTrue)
{
    Song other("Believer", "Imagine Dragons", 204, "resources/audio/believer.wav");
    EXPECT_TRUE(songWithAllFields != other);
}

TEST_F(GivenASong, WhenOperatorNotEqualsCalledWithIdenticalSong_ThenReturnsFalse)
{
    Song duplicate("berry", "Linkin Park", 185, "resources/audio/berry.wav");
    EXPECT_FALSE(songWithAllFields != duplicate);
}

TEST_F(GivenASong, WhenFormatDurationCalledWithZeroSeconds_ThenReturnsDoubleZero)
{
    EXPECT_EQ(Song::formatDuration(0), "00:00");
}

TEST_F(GivenASong, WhenFormatDurationCalledWith185Seconds_ThenReturns0305)
{
    EXPECT_EQ(Song::formatDuration(185), "03:05");
}

TEST_F(GivenASong, WhenFormatDurationCalledWith60Seconds_ThenReturns0100)
{
    EXPECT_EQ(Song::formatDuration(60), "01:00");
}

TEST_F(GivenASong, WhenFormatDurationCalledWith3600Seconds_ThenReturns6000)
{
    EXPECT_EQ(Song::formatDuration(3600), "60:00");
}

TEST_F(GivenASong, WhenStripExtensionCalledWithWavFilename_ThenExtensionIsRemoved)
{
    EXPECT_EQ(Song::stripExtension("berry.wav"), "berry");
}

TEST_F(GivenASong, WhenStripExtensionCalledWithNoExtension_ThenOriginalStringIsReturned)
{
    EXPECT_EQ(Song::stripExtension("berry"), "berry");
}

TEST_F(GivenASong, WhenStripExtensionCalledWithMultipleDots_ThenOnlyLastExtensionIsStripped)
{
    EXPECT_EQ(Song::stripExtension("my.song.wav"), "my.song");
}

TEST_F(GivenASong, WhenStripExtensionCalledWithEmptyString_ThenEmptyStringIsReturned)
{
    EXPECT_EQ(Song::stripExtension(""), "");
}

TEST_F(GivenASong, WhenReadDurationCalledWithNonExistentFile_ThenReturnsMinusOne)
{
    EXPECT_EQ(Song::readDuration("resources/audio/nonexistent.wav"), -1);
}

TEST_F(GivenASong, WhenReadDurationCalledWithEmptyPath_ThenReturnsMinusOne)
{
    EXPECT_EQ(Song::readDuration(""), -1);
}