#ifndef MOCKIAUDIOPLAYER_H
#define MOCKIAUDIOPLAYER_H

#include <gmock/gmock.h>
#include "IAudioPlayer.h"
#include "ErrorCode.h"

class MockIAudioPlayer : public IAudioPlayer
{
public:
    MOCK_METHOD(ErrorCode, play, (const std::string& filePath), (override));
    MOCK_METHOD(ErrorCode, pause, (), (override));
    MOCK_METHOD(ErrorCode, resume, (), (override));
    MOCK_METHOD(ErrorCode, stop, (), (override));
    MOCK_METHOD(int, getState, (), (override));
    MOCK_METHOD(bool, isSongFinished, (), (override));
};

#endif