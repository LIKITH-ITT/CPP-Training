#ifndef MOCKIPLAYLISTREPOSITORY_H
#define MOCKIPLAYLISTREPOSITORY_H

#include <gmock/gmock.h>
#include "IPlaylistRepository.h"
#include "Playlist.h"
#include "ErrorCode.h"

class MockIPlaylistRepository : public IPlaylistRepository
{
public:
    MOCK_METHOD(ErrorCode, save, (const Playlist& playlist), (override));
    MOCK_METHOD(ErrorCode, load, (const std::string& name, Playlist& out), (override));
    MOCK_METHOD(ErrorCode, remove, (const std::string& name), (override));
    MOCK_METHOD(std::vector<std::string>, listSaved, (), (override));
    MOCK_METHOD(std::vector<std::string>, listAudioFiles, (), (override));
};

#endif