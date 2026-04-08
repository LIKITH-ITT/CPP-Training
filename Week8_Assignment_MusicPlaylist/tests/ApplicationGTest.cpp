#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Application.h"
#include "MockIConsoleUI.h"
#include "MockIPlaylistManager.h"
#include "MockIPlaylistRepository.h"
#include "MockIAudioPlayer.h"
#include "SongNavigator.h"
#include "Playlist.h"
#include "Song.h"
#include "ErrorCode.h"

class GivenAnApplication : public ::testing::Test
{
protected:
    MockIConsoleUI mockUI;
    MockIPlaylistManager mockManager;
    MockIPlaylistRepository mockRepository;
    MockIAudioPlayer mockPlayer;
    SongNavigator navigator;
    Application* app;
    Playlist rockPlaylist;
    Playlist emptyPlaylist;
    Song song1;
    Song song2;

    void SetUp() override
    {
        rockPlaylist  = Playlist("rock");
        emptyPlaylist = Playlist("rock");
        song1 = Song("berry", "Unknown", 185, "resources/audio/numb.wav");
        song2 = Song("miradar", "Unknown", 204, "resources/audio/believer.wav");
        app   = new Application(&mockUI, &mockManager, &mockRepository, &mockPlayer, &navigator);
        EXPECT_CALL(mockUI, showMainMenu()).Times(::testing::AnyNumber());
        EXPECT_CALL(mockUI, showPlaylistMenu(::testing::_)).Times(::testing::AnyNumber());
        EXPECT_CALL(mockUI, showPlaylist(::testing::_)).Times(::testing::AnyNumber());
        EXPECT_CALL(mockUI, showMessage(::testing::_)).Times(::testing::AnyNumber());
        EXPECT_CALL(mockUI, showError(::testing::_)).Times(::testing::AnyNumber());
        EXPECT_CALL(mockUI, showAudioFiles(::testing::_)).Times(::testing::AnyNumber());
        EXPECT_CALL(mockUI, showSavedPlaylists(::testing::_)).Times(::testing::AnyNumber());
        EXPECT_CALL(mockUI, showPlaybackStatus(::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    }

    void TearDown() override
    {
        delete app;
    }

    void openRockPlaylist()
    {
        app->setActivePlaylistName("rock");
        navigator.setPlaylist(&rockPlaylist);
    }
};

TEST_F(GivenAnApplication, WhenHandlePlayIsCalledWithNoActivePlaylist_ThenReturnsPlaylistNotFound)
{
    EXPECT_EQ(app->handlePlay(), ErrorCode::PLAYLIST_NOT_FOUND);
}

TEST_F(GivenAnApplication, WhenHandlePlayIsCalledWithEmptyPlaylist_ThenReturnsEmptyPlaylist)
{
    EXPECT_CALL(mockManager, getPlaylist("rock")).WillRepeatedly(::testing::ReturnRef(emptyPlaylist));
    app->setActivePlaylistName("rock");
    EXPECT_EQ(app->handlePlay(), ErrorCode::EMPTY_PLAYLIST);
}

TEST_F(GivenAnApplication, WhenHandlePlayIsCalledWhileStopped_ThenCallsPlayerPlayWithCorrectFilePath)
{
    rockPlaylist.addSong(song1);
    openRockPlaylist();
    EXPECT_CALL(mockManager, getPlaylist("rock")).WillRepeatedly(::testing::ReturnRef(rockPlaylist));
    EXPECT_CALL(mockPlayer, getState()).WillOnce(::testing::Return(IAudioPlayer::STATE_STOPPED));
    EXPECT_CALL(mockPlayer, play("resources/audio/numb.wav")).WillOnce(::testing::Return(ErrorCode::SUCCESS));
    EXPECT_EQ(app->handlePlay(), ErrorCode::SUCCESS);
}

TEST_F(GivenAnApplication, WhenHandlePlayIsCalledWhilePaused_ThenCallsResumeAndNotPlay)
{
    rockPlaylist.addSong(song1);
    openRockPlaylist();
    EXPECT_CALL(mockManager, getPlaylist("rock")).WillRepeatedly(::testing::ReturnRef(rockPlaylist));
    EXPECT_CALL(mockPlayer, getState()).WillOnce(::testing::Return(IAudioPlayer::STATE_PAUSED));
    EXPECT_CALL(mockPlayer, resume()).WillOnce(::testing::Return(ErrorCode::SUCCESS));
    EXPECT_CALL(mockPlayer, play(::testing::_)).Times(0);
    EXPECT_EQ(app->handlePlay(), ErrorCode::SUCCESS);
}

TEST_F(GivenAnApplication, WhenHandlePlayIsCalledAndPlayerReturnsFileNotFound_ThenReturnsFileNotFound)
{
    rockPlaylist.addSong(song1);
    openRockPlaylist();
    EXPECT_CALL(mockManager, getPlaylist("rock")).WillRepeatedly(::testing::ReturnRef(rockPlaylist));
    EXPECT_CALL(mockPlayer, getState()).WillOnce(::testing::Return(IAudioPlayer::STATE_STOPPED));
    EXPECT_CALL(mockPlayer, play(::testing::_)).WillOnce(::testing::Return(ErrorCode::FILE_NOT_FOUND));
    EXPECT_EQ(app->handlePlay(), ErrorCode::FILE_NOT_FOUND);
}

TEST_F(GivenAnApplication, WhenHandlePauseIsCalledWhilePlaying_ThenReturnsSuccess)
{
    EXPECT_CALL(mockPlayer, pause()).WillOnce(::testing::Return(ErrorCode::SUCCESS));
    EXPECT_EQ(app->handlePause(), ErrorCode::SUCCESS);
}

TEST_F(GivenAnApplication, WhenHandlePauseIsCalledWhileNotPlaying_ThenReturnsNothingPlaying)
{
    EXPECT_CALL(mockPlayer, pause()).WillOnce(::testing::Return(ErrorCode::NOTHING_PLAYING));
    EXPECT_EQ(app->handlePause(), ErrorCode::NOTHING_PLAYING);
}

TEST_F(GivenAnApplication, WhenHandleStopIsCalledWhilePlaying_ThenReturnsSuccess)
{
    EXPECT_CALL(mockPlayer, stop()).WillOnce(::testing::Return(ErrorCode::SUCCESS));
    EXPECT_EQ(app->handleStop(), ErrorCode::SUCCESS);
}

TEST_F(GivenAnApplication, WhenHandleStopIsCalledWhileAlreadyStopped_ThenReturnsAlreadyStopped)
{
    EXPECT_CALL(mockPlayer, stop()).WillOnce(::testing::Return(ErrorCode::ALREADY_STOPPED));
    EXPECT_EQ(app->handleStop(), ErrorCode::ALREADY_STOPPED);
}

TEST_F(GivenAnApplication, WhenHandleNextIsCalledWithNoActivePlaylist_ThenReturnsPlaylistNotFound)
{
    EXPECT_EQ(app->handleNext(), ErrorCode::PLAYLIST_NOT_FOUND);
}

TEST_F(GivenAnApplication, WhenHandleNextIsCalledWithEmptyPlaylist_ThenReturnsEmptyPlaylist)
{
    EXPECT_CALL(mockManager, getPlaylist("rock")).WillRepeatedly(::testing::ReturnRef(emptyPlaylist));
    app->setActivePlaylistName("rock");
    EXPECT_EQ(app->handleNext(), ErrorCode::EMPTY_PLAYLIST);
}

TEST_F(GivenAnApplication, WhenHandleNextIsCalledWithTwoSongs_ThenPlaysSecondSong)
{
    rockPlaylist.addSong(song1);
    rockPlaylist.addSong(song2);
    openRockPlaylist();
    EXPECT_CALL(mockManager, getPlaylist("rock")).WillRepeatedly(::testing::ReturnRef(rockPlaylist));
    EXPECT_CALL(mockPlayer, play("resources/audio/believer.wav")).WillOnce(::testing::Return(ErrorCode::SUCCESS));
    EXPECT_EQ(app->handleNext(), ErrorCode::SUCCESS);
}

TEST_F(GivenAnApplication, WhenHandleNextIsCalledAtLastSong_ThenWrapsAroundAndPlaysFirstSong)
{
    rockPlaylist.addSong(song1);
    rockPlaylist.addSong(song2);
    openRockPlaylist();
    navigator.next();
    EXPECT_CALL(mockManager, getPlaylist("rock")).WillRepeatedly(::testing::ReturnRef(rockPlaylist));
    EXPECT_CALL(mockPlayer, play("resources/audio/numb.wav")).WillOnce(::testing::Return(ErrorCode::SUCCESS));
    EXPECT_EQ(app->handleNext(), ErrorCode::SUCCESS);
}

TEST_F(GivenAnApplication, WhenHandlePrevIsCalledWithNoActivePlaylist_ThenReturnsPlaylistNotFound)
{
    EXPECT_EQ(app->handlePrev(), ErrorCode::PLAYLIST_NOT_FOUND);
}

TEST_F(GivenAnApplication, WhenHandlePrevIsCalledWithEmptyPlaylist_ThenReturnsEmptyPlaylist)
{
    EXPECT_CALL(mockManager, getPlaylist("rock")).WillRepeatedly(::testing::ReturnRef(emptyPlaylist));
    app->setActivePlaylistName("rock");
    EXPECT_EQ(app->handlePrev(), ErrorCode::EMPTY_PLAYLIST);
}

TEST_F(GivenAnApplication, WhenHandlePrevIsCalledFromFirstSong_ThenWrapsAroundAndPlaysLastSong)
{
    rockPlaylist.addSong(song1);
    rockPlaylist.addSong(song2);
    openRockPlaylist();
    EXPECT_CALL(mockManager, getPlaylist("rock")).WillRepeatedly(::testing::ReturnRef(rockPlaylist));
    EXPECT_CALL(mockPlayer, play("resources/audio/believer.wav")).WillOnce(::testing::Return(ErrorCode::SUCCESS));
    EXPECT_EQ(app->handlePrev(), ErrorCode::SUCCESS);
}

TEST_F(GivenAnApplication, WhenHandleSaveAndPlaylistCalledWithNoActivePlaylist_ThenReturnsPlaylistNotFound)
{
    EXPECT_EQ(app->handleSavePlaylist(), ErrorCode::PLAYLIST_NOT_FOUND);
}

TEST_F(GivenAnApplication, WhenHandleSaveAndPlaylistCalledWithActivePlaylist_ThenCallsRepoSaveAndReturnsSuccess)
{
    rockPlaylist.addSong(song1);
    EXPECT_CALL(mockManager, getPlaylist("rock")).WillRepeatedly(::testing::ReturnRef(rockPlaylist));
    EXPECT_CALL(mockRepository, save(::testing::_)).WillOnce(::testing::Return(ErrorCode::SUCCESS));
    app->setActivePlaylistName("rock");
    EXPECT_EQ(app->handleSavePlaylist(), ErrorCode::SUCCESS);
}

TEST_F(GivenAnApplication, WhenHandleSaveAndPlaylistCalledAndWriteFails_ThenReturnsFileWriteError)
{
    EXPECT_CALL(mockManager, getPlaylist("rock")).WillRepeatedly(::testing::ReturnRef(rockPlaylist));
    EXPECT_CALL(mockRepository, save(::testing::_)).WillOnce(::testing::Return(ErrorCode::FILE_WRITE_ERROR));
    app->setActivePlaylistName("rock");
    EXPECT_EQ(app->handleSavePlaylist(), ErrorCode::FILE_WRITE_ERROR);
}

TEST_F(GivenAnApplication, WhenHandleCreateAndPlaylistCalledWithEmptyName_ThenReturnsInvalidInput)
{
    EXPECT_CALL(mockUI, prompt(::testing::_)).WillOnce(::testing::Return(""));
    EXPECT_EQ(app->handleCreatePlaylist(), ErrorCode::INVALID_INPUT);
}

TEST_F(GivenAnApplication, WhenHandleCreateAndPlaylistCalledWithDuplicateName_ThenReturnsPlaylistAlreadyExists)
{
    EXPECT_CALL(mockUI, prompt(::testing::_)).WillOnce(::testing::Return("rock"));
    EXPECT_CALL(mockManager, createPlaylist("rock")).WillOnce(::testing::Return(ErrorCode::PLAYLIST_ALREADY_EXISTS));
    EXPECT_EQ(app->handleCreatePlaylist(), ErrorCode::PLAYLIST_ALREADY_EXISTS);
}

TEST_F(GivenAnApplication, WhenHandleCreateAndPlaylistCalledWithValidName_ThenCallsManagerCreateAndReturnsSuccess)
{
    EXPECT_CALL(mockUI, prompt(::testing::_)).WillOnce(::testing::Return("rock"));
    EXPECT_CALL(mockManager, createPlaylist("rock")).WillOnce(::testing::Return(ErrorCode::SUCCESS));
    EXPECT_CALL(mockManager, getPlaylist("rock")).WillRepeatedly(::testing::ReturnRef(rockPlaylist));
    EXPECT_CALL(mockUI, getInput()).WillOnce(::testing::Return("12"));
    EXPECT_CALL(mockPlayer, stop()).WillRepeatedly(::testing::Return(ErrorCode::SUCCESS));
    EXPECT_EQ(app->handleCreatePlaylist(), ErrorCode::SUCCESS);
}

TEST_F(GivenAnApplication, WhenHandleDeleteAndPlaylistCalledWithNoSavedPlaylists_ThenReturnsFileNotFound)
{
    EXPECT_CALL(mockRepository, listSaved()).WillOnce(::testing::Return(std::vector<std::string>()));
    EXPECT_EQ(app->handleDeletePlaylist(), ErrorCode::FILE_NOT_FOUND);
}

TEST_F(GivenAnApplication, WhenHandleDeleteAndPlaylistCalledWithEmptyInput_ThenReturnsInvalidInput)
{
    std::vector<std::string> saved = {"rock"};
    EXPECT_CALL(mockRepository, listSaved()).WillOnce(::testing::Return(saved));
    EXPECT_CALL(mockUI, prompt(::testing::_)).WillOnce(::testing::Return(""));
    EXPECT_EQ(app->handleDeletePlaylist(), ErrorCode::INVALID_INPUT);
}

TEST_F(GivenAnApplication, WhenHandleDeleteAndPlaylistCalledWithValidName_ThenCallsRepoRemoveAndManagerDelete)
{
    std::vector<std::string> saved = {"rock"};
    EXPECT_CALL(mockRepository, listSaved()).WillOnce(::testing::Return(saved));
    EXPECT_CALL(mockUI, prompt(::testing::_)).WillOnce(::testing::Return("rock"));
    EXPECT_CALL(mockRepository, remove("rock")).WillOnce(::testing::Return(ErrorCode::SUCCESS));
    EXPECT_CALL(mockManager, deletePlaylist("rock")).WillOnce(::testing::Return(ErrorCode::SUCCESS));
    EXPECT_EQ(app->handleDeletePlaylist(), ErrorCode::SUCCESS);
}

TEST_F(GivenAnApplication, WhenHandleDeleteAndPlaylistCalledWithNonExistentName_ThenReturnsFileNotFound)
{
    std::vector<std::string> saved = {"rock"};
    EXPECT_CALL(mockRepository, listSaved()).WillOnce(::testing::Return(saved));
    EXPECT_CALL(mockUI, prompt(::testing::_)).WillOnce(::testing::Return("jazz"));
    EXPECT_CALL(mockRepository, remove("jazz")).WillOnce(::testing::Return(ErrorCode::FILE_NOT_FOUND));
    EXPECT_EQ(app->handleDeletePlaylist(), ErrorCode::FILE_NOT_FOUND);
}

TEST_F(GivenAnApplication, WhenHandleRemoveSongIsCalledWithNoActivePlaylist_ThenReturnsPlaylistNotFound)
{
    EXPECT_EQ(app->handleRemoveSong(), ErrorCode::PLAYLIST_NOT_FOUND);
}

TEST_F(GivenAnApplication, WhenHandleRemoveSongIsCalledWithEmptyPlaylist_ThenReturnsEmptyPlaylist)
{
    EXPECT_CALL(mockManager, getPlaylist("rock")).WillRepeatedly(::testing::ReturnRef(emptyPlaylist));
    app->setActivePlaylistName("rock");
    EXPECT_EQ(app->handleRemoveSong(), ErrorCode::EMPTY_PLAYLIST);
}

TEST_F(GivenAnApplication, WhenHandleRemoveSongIsCalledWithNonNumericInput_ThenReturnsInvalidIndex)
{
    rockPlaylist.addSong(song1);
    EXPECT_CALL(mockManager, getPlaylist("rock")).WillRepeatedly(::testing::ReturnRef(rockPlaylist));
    EXPECT_CALL(mockUI, prompt(::testing::_)).WillOnce(::testing::Return("abc"));
    app->setActivePlaylistName("rock");
    EXPECT_EQ(app->handleRemoveSong(), ErrorCode::INVALID_INDEX);
}

TEST_F(GivenAnApplication, WhenHandleRemoveSongIsCalledWithValidIndex_ThenCallsManagerRemoveSongAndReturnsSuccess)
{
    rockPlaylist.addSong(song1);
    openRockPlaylist();
    EXPECT_CALL(mockManager, getPlaylist("rock")).WillRepeatedly(::testing::ReturnRef(rockPlaylist));
    EXPECT_CALL(mockUI, prompt(::testing::_)).WillOnce(::testing::Return("1"));
    EXPECT_CALL(mockManager, removeSong("rock", 0)).WillOnce(::testing::Return(ErrorCode::SUCCESS));
    EXPECT_EQ(app->handleRemoveSong(), ErrorCode::SUCCESS);
}

TEST_F(GivenAnApplication, WhenHandleMoveSongUpIsCalledWithNoActivePlaylist_ThenReturnsPlaylistNotFound)
{
    EXPECT_EQ(app->handleMoveSongUp(), ErrorCode::PLAYLIST_NOT_FOUND);
}

TEST_F(GivenAnApplication, WhenHandleMoveSongUpIsCalledWithEmptyPlaylist_ThenReturnsEmptyPlaylist)
{
    EXPECT_CALL(mockManager, getPlaylist("rock")).WillRepeatedly(::testing::ReturnRef(emptyPlaylist));
    app->setActivePlaylistName("rock");
    EXPECT_EQ(app->handleMoveSongUp(), ErrorCode::EMPTY_PLAYLIST);
}

TEST_F(GivenAnApplication, WhenHandleMoveSongDownIsCalledWithNoActivePlaylist_ThenReturnsPlaylistNotFound)
{
    EXPECT_EQ(app->handleMoveSongDown(), ErrorCode::PLAYLIST_NOT_FOUND);
}

TEST_F(GivenAnApplication, WhenHandleMoveSongDownIsCalledWithEmptyPlaylist_ThenReturnsEmptyPlaylist)
{
    EXPECT_CALL(mockManager, getPlaylist("rock")).WillRepeatedly(::testing::ReturnRef(emptyPlaylist));
    app->setActivePlaylistName("rock");
    EXPECT_EQ(app->handleMoveSongDown(), ErrorCode::EMPTY_PLAYLIST);
}