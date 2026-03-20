#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>
#include "Song.h"
#include "ErrorCode.h"

class Playlist
{
public:
    std::string name;
    std::vector<Song> songs;

    Playlist();
    explicit Playlist(const std::string& aName);

    ErrorCode addSong(const Song& song);
    ErrorCode removeSong(int index);
    ErrorCode moveSongUp(int index);
    ErrorCode moveSongDown(int index);

    Song& getSong(int index);
    const Song& getSong(int index) const;

    int size() const;
    bool isEmpty() const;
};

#endif