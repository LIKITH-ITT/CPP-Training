#ifndef SONG_H
#define SONG_H

#include <string>
#include <SFML/Audio.hpp>

class Song
{
public:
    std::string title;
    std::string artist;
    int duration;
    std::string filePath;

    Song();
    Song(const std::string& aTitle, const std::string& aArtist, int aDuration, const std::string& aFilePath);

    bool operator==(const Song& other) const;
    bool operator!=(const Song& other) const;

    static int readDuration(const std::string& aFilePath);
    static std::string stripExtension(const std::string& filename);
    static std::string formatDuration(int seconds);
};

#endif
