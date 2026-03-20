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

int Song::readDuration(const std::string& aFilePath)
{
    int time = 0;
    std::ifstream file(aFilePath.c_str(), std::ios::binary);
    if (!file.is_open())
    {
        time = -1;
    }

    file.seekg(28);
    int byteRate = 0;
    file.read(reinterpret_cast<char*>(&byteRate), sizeof(byteRate));

    if (!file || byteRate <= 0)
    {
        time = -1;
    }

    file.seekg(12);

    char chunkId[4];
    int  chunkSize = 0;

    while (file.read(chunkId, 4) && file.read(reinterpret_cast<char*>(&chunkSize), 4))
    {
        if (chunkId[0] == 'd' && chunkId[1] == 'a' &&  chunkId[2] == 't' && chunkId[3] == 'a')
        { 
            if (chunkSize <= 0)
                time = -1;
            time = chunkSize / byteRate;
        }

        int skipSize = chunkSize + (chunkSize % 2);
        file.seekg(skipSize, std::ios::cur);

        if (!file.good())
        {  break;
        }
    }

    file.seekg(0, std::ios::end);
    int fileSize = static_cast<int>(file.tellg());
    if (fileSize > 44)
    {
        time = (fileSize - 44) / byteRate;
    }

    return time;
}

std::string Song::stripExtension(const std::string& filename)
{
    size_t dot = filename.rfind('.');
    if (dot == std::string::npos)
    {
        return filename;
    }
    return filename.substr(0, dot);
}

std::string Song::formatDuration(int seconds)
{
    if (seconds < 0) return "--:--";
    int mins = seconds / 60;
    int secs = seconds % 60;
    std::string result;
    result += (mins < 10 ? "0" : "") + std::to_string(mins);
    result += ":";
    result += (secs < 10 ? "0" : "") + std::to_string(secs);
    return result;
}
