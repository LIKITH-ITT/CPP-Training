#include "SystemAudioPlayer.h"
#include <fstream>
#include <cstdlib>
#include <string>


SystemAudioPlayer::SystemAudioPlayer()
    : state_(IAudioPlayer::STATE_STOPPED)
{}

SystemAudioPlayer::~SystemAudioPlayer()
{
    if (state_ != IAudioPlayer::STATE_STOPPED)
    {
        killProcess();
    }
}

ErrorCode SystemAudioPlayer::play(const std::string& filePath)
{
    std::ifstream file(filePath.c_str());
    if (!file.is_open())
    {
        return ErrorCode::FILE_NOT_FOUND;
    }
    file.close();

    killProcess();

    std::string command;

#ifdef __APPLE__
    command = "afplay \"" + filePath + "\" &";
#else
    command = "aplay \"" + filePath + "\" > /dev/null 2>&1 &";
#endif

    std::system(command.c_str());
    state_ = IAudioPlayer::STATE_PLAYING;
    return ErrorCode::SUCCESS;
}

ErrorCode SystemAudioPlayer::pause()
{
    if (state_ != IAudioPlayer::STATE_PLAYING)
    {
        return ErrorCode::NOTHING_PLAYING;
    }

#ifdef __APPLE__
    std::system("kill -STOP $(pgrep afplay) 2>/dev/null");
#else
    std::system("kill -STOP $(pgrep aplay) 2>/dev/null");
#endif

    state_ = IAudioPlayer::STATE_PAUSED;
    return ErrorCode::SUCCESS;
}

ErrorCode SystemAudioPlayer::resume()
{
    if (state_ != IAudioPlayer::STATE_PAUSED)
    {
        return ErrorCode::NOTHING_PLAYING;
    }

#ifdef __APPLE__
    std::system("kill -CONT $(pgrep afplay) 2>/dev/null");
#else
    std::system("kill -CONT $(pgrep aplay) 2>/dev/null");
#endif

    state_ = IAudioPlayer::STATE_PLAYING;
    return ErrorCode::SUCCESS;
}

ErrorCode SystemAudioPlayer::stop()
{
    if (state_ == IAudioPlayer::STATE_STOPPED)
    {
        return ErrorCode::ALREADY_STOPPED;
    }

    killProcess();
    state_ = IAudioPlayer::STATE_STOPPED;
    return ErrorCode::SUCCESS;
}

int SystemAudioPlayer::getState()
{
    return state_;
}

void SystemAudioPlayer::killProcess()
{
#ifdef __APPLE__
    std::system("killall afplay 2>/dev/null");
#else
    std::system("killall aplay 2>/dev/null");
#endif
}
