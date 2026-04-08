#ifndef IAUDIOPLAYER_H
#define IAUDIOPLAYER_H

#include "ErrorCode.h"
#include <string>

class IAudioPlayer
{
public:
    static const int STATE_STOPPED = 0;
    static const int STATE_PLAYING = 1;
    static const int STATE_PAUSED  = 2;

    virtual ~IAudioPlayer() {}

    virtual ErrorCode play(const std::string& filePath) = 0;
    virtual ErrorCode pause() = 0;
    virtual ErrorCode resume() = 0;
    virtual ErrorCode stop() = 0;
    virtual int getState() = 0;
    virtual bool isSongFinished() = 0;
};

#endif
