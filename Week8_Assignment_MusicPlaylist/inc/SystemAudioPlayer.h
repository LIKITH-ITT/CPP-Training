#ifndef SYSTEMAUDIOPLAYER_H
#define SYSTEMAUDIOPLAYER_H

#include <string>
#include <SFML/Audio.hpp>
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
    bool isSongFinished();

private:
    sf::Music music_;
    bool stoppedByUser_;
};

#endif
