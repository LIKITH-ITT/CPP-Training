#include "SystemAudioPlayer.h"
#include <fstream>
#include <string>

SystemAudioPlayer::SystemAudioPlayer() : stoppedByUser_(false)
{}

SystemAudioPlayer::~SystemAudioPlayer()
{
    music_.stop();
}

ErrorCode SystemAudioPlayer::play(const std::string& filePath)
{
    ErrorCode errorCode = ErrorCode::SUCCESS;
    std::ifstream file(filePath.c_str());
    if (!file.is_open())
    {
        errorCode = ErrorCode::FILE_NOT_FOUND;
    }
    file.close();

    music_.stop();

    if (!music_.openFromFile(filePath))
    {
        errorCode = ErrorCode::FILE_READ_ERROR;
    }

    music_.setLoop(false);
    music_.play();
    stoppedByUser_ = false;
    return errorCode;
}

ErrorCode SystemAudioPlayer::pause()
{
    ErrorCode errorCode = ErrorCode::SUCCESS;
    if (music_.getStatus() != sf::Music::Playing)
    {
        errorCode = ErrorCode::NOTHING_PLAYING;
    }
    music_.pause();
    return errorCode;
}

ErrorCode SystemAudioPlayer::resume()
{
    ErrorCode errorCode = ErrorCode::SUCCESS;
    if (music_.getStatus() != sf::Music::Paused)
    {
        errorCode = ErrorCode::NOTHING_PLAYING;
    }
    music_.play();
    return errorCode;
}

ErrorCode SystemAudioPlayer::stop()
{
    ErrorCode errorCode = ErrorCode::SUCCESS;
    if (music_.getStatus() == sf::Music::Stopped && stoppedByUser_)
    {
        errorCode = ErrorCode::ALREADY_STOPPED;
    }
    music_.stop();
    stoppedByUser_ = true;
    return errorCode;
}

int SystemAudioPlayer::getState()
{
    int state = IAudioPlayer::STATE_STOPPED;
    switch (music_.getStatus())
    {
        case sf::Music::Playing: 
            state = IAudioPlayer::STATE_PLAYING;
        case sf::Music::Paused:  
            state = IAudioPlayer::STATE_PAUSED;
    }
    return state;
}

bool SystemAudioPlayer::isSongFinished()
{
    return music_.getStatus() == sf::Music::Stopped && !stoppedByUser_;
}