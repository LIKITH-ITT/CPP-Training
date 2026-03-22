#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "PlaylistRepository.h"
#include "Playlist.h"
#include "Song.h"
#include "ErrorCode.h"

static const std::string TEST_NAME = "test_playlist";

class GivenAPlaylistRepository : public ::testing::Test
{
protected:
    PlaylistRepository repo;

    void SetUp() override
    {
        std::remove(("resources/playlists/" + TEST_NAME + ".txt").c_str());
    }

    void TearDown() override
    {
        std::remove(("resources/playlists/" + TEST_NAME + ".txt").c_str());
    }
};

class GivenAPlaylistRepositoryWithSavedPlaylist : public ::testing::Test
{
protected:
    PlaylistRepository repo;
    Playlist savedPlaylist;

    void SetUp() override
    {
        savedPlaylist = Playlist(TEST_NAME);
        savedPlaylist.addSong(Song("berry", "Unknown", 185, "resources/audio/berry.wav"));
        savedPlaylist.addSong(Song("miradar", "Imagine Dragons", 204, "resources/audio/miradar.wav"));
        repo.save(savedPlaylist);
    }

    void TearDown() override
    {
        std::remove(("resources/playlists/" + TEST_NAME + ".txt").c_str());
    }
};

TEST_F(GivenAPlaylistRepository, WhenSaveCalledWithEmptyPlaylist_ThenReturnsSuccess)
{
    Playlist empty(TEST_NAME);
    EXPECT_EQ(repo.save(empty), ErrorCode::SUCCESS);
}

TEST_F(GivenAPlaylistRepository, WhenSaveCalledWithPlaylistWithSongs_ThenReturnsSuccess)
{
    Playlist p(TEST_NAME);
    p.addSong(Song("berry", "Unknown", 185, "resources/audio/berry.wav"));
    EXPECT_EQ(repo.save(p), ErrorCode::SUCCESS);
}

TEST_F(GivenAPlaylistRepository, WhenSaveCalledWithPlaylist_ThenFileIsCreatedOnDisk)
{
    Playlist p(TEST_NAME);
    repo.save(p);
    std::ifstream f("resources/playlists/" + TEST_NAME + ".txt");
    EXPECT_TRUE(f.is_open());
}

TEST_F(GivenAPlaylistRepository, WhenLoadCalledWithNonExistentFile_ThenReturnsFileNotFound)
{
    Playlist out;
    EXPECT_EQ(repo.load("does_not_exist", out), ErrorCode::FILE_NOT_FOUND);
}

TEST_F(GivenAPlaylistRepositoryWithSavedPlaylist, WhenLoadCalledWithExistingFile_ThenReturnsSuccess)
{
    Playlist loaded;
    EXPECT_EQ(repo.load(TEST_NAME, loaded), ErrorCode::SUCCESS);
}

TEST_F(GivenAPlaylistRepositoryWithSavedPlaylist, WhenLoadCalledWithExistingFile_ThenPlaylistNameIsRestored)
{
    Playlist loaded;
    repo.load(TEST_NAME, loaded);
    EXPECT_EQ(loaded.name, TEST_NAME);
}

TEST_F(GivenAPlaylistRepositoryWithSavedPlaylist, WhenLoadCalledWithExistingFile_ThenCorrectNumberOfSongsIsRestored)
{
    Playlist loaded;
    repo.load(TEST_NAME, loaded);
    EXPECT_EQ(loaded.size(), 2u);
}

TEST_F(GivenAPlaylistRepositoryWithSavedPlaylist, WhenLoadCalledWithExistingFile_ThenFirstSongFieldsAreRestoredCorrectly)
{
    Playlist loaded;
    repo.load(TEST_NAME, loaded);
    EXPECT_EQ(loaded.getSong(0).title, "berry");
    EXPECT_EQ(loaded.getSong(0).artist, "Unknown");
    EXPECT_EQ(loaded.getSong(0).duration, 185);
    EXPECT_EQ(loaded.getSong(0).filePath, "resources/audio/berry.wav");
}

TEST_F(GivenAPlaylistRepositoryWithSavedPlaylist, WhenLoadCalledWithExistingFile_ThenSongsAreRestoredInCorrectOrder)
{
    Playlist loaded;
    repo.load(TEST_NAME, loaded);
    EXPECT_EQ(loaded.getSong(0).title, "berry");
    EXPECT_EQ(loaded.getSong(1).title, "miradar");
}

TEST_F(GivenAPlaylistRepository, WhenSaveAndLoadCalledInSequence_ThenAllFieldsAreFullyRestored)
{
    Playlist original(TEST_NAME);
    original.addSong(Song("berry", "Unknown", 185, "resources/audio/berry.wav"));
    original.addSong(Song("miradar", "Imagine Dragons", 204, "resources/audio/miradar.wav"));
    repo.save(original);

    Playlist restored;
    repo.load(TEST_NAME, restored);

    EXPECT_EQ(restored.name, original.name);
    EXPECT_EQ(restored.size(), original.size());
    EXPECT_EQ(restored.getSong(0).title, original.getSong(0).title);
    EXPECT_EQ(restored.getSong(1).title, original.getSong(1).title);
}

TEST_F(GivenAPlaylistRepositoryWithSavedPlaylist, WhenRemoveCalledWithExistingFile_ThenReturnsSuccess)
{
    EXPECT_EQ(repo.remove(TEST_NAME), ErrorCode::SUCCESS);
}

TEST_F(GivenAPlaylistRepository, WhenRemoveCalledWithNonExistentFile_ThenReturnsFileNotFound)
{
    EXPECT_EQ(repo.remove("nonexistent"), ErrorCode::FILE_NOT_FOUND);
}

TEST_F(GivenAPlaylistRepositoryWithSavedPlaylist, WhenRemoveCalledWithExistingFile_ThenFileIsDeletedFromDisk)
{
    repo.remove(TEST_NAME);
    std::ifstream f("resources/playlists/" + TEST_NAME + ".txt");
    EXPECT_FALSE(f.is_open());
}

TEST_F(GivenAPlaylistRepositoryWithSavedPlaylist, WhenListSavedCalled_ThenSavedPlaylistNameIsPresent)
{
    std::vector<std::string> names = repo.listSaved();
    bool found = false;
    for (int index = 0; index < names.size(); ++index)
    {
        if (names[index] == TEST_NAME) { found = true; break; }
    }
    EXPECT_TRUE(found);
}

TEST_F(GivenAPlaylistRepositoryWithSavedPlaylist, WhenListSavedCalledAfterRemove_ThenPlaylistNameIsNotPresent)
{
    repo.remove(TEST_NAME);
    std::vector<std::string> names = repo.listSaved();
    bool found = false;
    for (size_t index = 0; index < names.size(); ++index)
    {
        if (names[index] == TEST_NAME) { found = true; break; }
    }
    EXPECT_FALSE(found);
}