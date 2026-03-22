#ifndef SONGNAVIGATOR_H
#define SONGNAVIGATOR_H

#include "Playlist.h"
#include "Song.h"
#include "ErrorCode.h"

class SongNavigator
{
public:
    SongNavigator();
    ~SongNavigator() {}

    ErrorCode setPlaylist(const Playlist* playlist);
    Song next();
    Song prev();
    Song current() const;
    bool hasCurrentSong() const;
    ErrorCode reset();
    int getCurrentIndex() const;

private:
    const Playlist* playlist_;
    int currentIndex_;
};

#endif
