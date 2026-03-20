#include "Playlist.h"
#include <algorithm>

Playlist::Playlist() : name("") {}

Playlist::Playlist(const std::string& name) : name(name) {}

ErrorCode Playlist::addSong(const Song& song)
{
    songs.push_back(song);
    return ErrorCode::SUCCESS;
}

ErrorCode Playlist::removeSong(int index)
{
    if (index < 0 || index >= songs.size())
    {
        return ErrorCode::INVALID_INDEX;
    }

    songs.erase(songs.begin() + index);
    return ErrorCode::SUCCESS;
}

ErrorCode Playlist::moveSongUp(int index)
{
    if (index <= 0 || index >= songs.size())
    {
        return ErrorCode::INVALID_INDEX;
    }

    std::swap(songs[index], songs[index - 1]);
    return ErrorCode::SUCCESS;
}

ErrorCode Playlist::moveSongDown(int index)
{
    if (index < 0 || index >= songs.size() - 1)
    {
        return ErrorCode::INVALID_INDEX;
    }

    std::swap(songs[index], songs[index + 1]);
    return ErrorCode::SUCCESS;
}

Song& Playlist::getSong(int index)
{
    return songs[index];
}

const Song& Playlist::getSong(int index) const
{
    return songs[index];
}

int Playlist::size() const
{
    return songs.size();
}

bool Playlist::isEmpty() const
{
    return songs.empty();
}