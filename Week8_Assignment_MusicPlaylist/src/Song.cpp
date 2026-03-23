#include "Song.h"
#include <fstream>
#include <string>

Song::Song() : title("") , artist("") , duration(0) , filePath("")
{}

Song::Song(const std::string& Title, const std::string& Artist, int Duration, const std::string& FilePath)
: title(Title), artist(Artist), duration(Duration), filePath(FilePath)
{}


bool Song::operator==(const Song& other) const
{
    return title == other.title && artist == other.artist && filePath == other.filePath;
}

bool Song::operator!=(const Song& other) const
{
    return !(*this == other);
}

std::string Song::stripExtension(const std::string& filename)
{
    int dot = filename.rfind('.');
    if (dot == std::string::npos)
    {
        return filename;
    }
    return filename.substr(0, dot);
}

std::string Song::formatDuration(int seconds)
{
    if (seconds < 0) return "--";
    int mins = seconds / 60;
    int secs = seconds % 60;
    std::string result;
    result += (mins < 10 ? "0" : "") + std::to_string(mins);
    result += ":";
    result += (secs < 10 ? "0" : "") + std::to_string(secs);
    return result;
}
int Song::readDuration(const std::string& filePath)
{
    sf::SoundBuffer buffer;

    if (!buffer.loadFromFile(filePath))
    {
        return -1;
    }

    return buffer.getDuration().asSeconds();
}