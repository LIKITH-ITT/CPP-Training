#ifndef IPLAYLISTREPOSITORY_H
#define IPLAYLISTREPOSITORY_H

#include <string>
#include <vector>
#include "Playlist.h"
#include "ErrorCode.h"

class IPlaylistRepository
{
public:
    virtual ~IPlaylistRepository() {}

    virtual ErrorCode save(const Playlist& playlist) = 0;
    virtual ErrorCode load(const std::string& name, Playlist& out) = 0;
    virtual ErrorCode remove(const std::string& name) = 0;
    virtual std::vector<std::string> listSaved() = 0;
    virtual std::vector<std::string> listAudioFiles() = 0;
};

#endif
