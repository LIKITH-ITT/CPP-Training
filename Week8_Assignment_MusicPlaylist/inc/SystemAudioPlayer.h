#ifndef SYSTEMAUDIOPLAYER_H
#define SYSTEMAUDIOPLAYER_H

#include <string>
#include "IAudioPlayer.h"
#include "ErrorCode.h"

class SystemAudioPlayer : public IAudioPlayer
{
public:
    SystemAudioPlayer();
    ~SystemAudioPlayer();

    ErrorCode play(const std::string& filePath);
    ErrorCode pause();
    ErrorCode resume();
    ErrorCode stop();
    int getState();

private:
    int state_;
    void killProcess();
};

#endif
