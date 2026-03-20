#ifndef ERRORCODE_H
#define ERRORCODE_H

#include <string>

enum class ErrorCode
{
    SUCCESS = 0,
    PLAYLIST_ALREADY_EXISTS,
    PLAYLIST_NOT_FOUND,
    SONG_NOT_FOUND,
    INVALID_INDEX,
    FILE_NOT_FOUND,
    FILE_READ_ERROR,
    FILE_WRITE_ERROR,
    NOTHING_PLAYING,
    ALREADY_STOPPED,
    EMPTY_PLAYLIST,
    INVALID_INPUT
};

inline std::string errorToString(ErrorCode code)
{
    std::string ErrorMessage;
    switch (code)
    {
        case ErrorCode::SUCCESS: 
            ErrorMessage = "Success.";
        case ErrorCode::PLAYLIST_ALREADY_EXISTS: 
            ErrorMessage = "Error: Playlist already exists.";
        case ErrorCode::PLAYLIST_NOT_FOUND: 
            ErrorMessage = "Error: Playlist not found.";
        case ErrorCode::SONG_NOT_FOUND: 
            ErrorMessage = "Error: Song not found.";
        case ErrorCode::INVALID_INDEX: 
            ErrorMessage = "Error: Invalid song index.";
        case ErrorCode::FILE_NOT_FOUND: 
            ErrorMessage = "Error: File not found.";
        case ErrorCode::FILE_READ_ERROR: 
            ErrorMessage = "Error: Failed to read file.";
        case ErrorCode::FILE_WRITE_ERROR: 
            ErrorMessage = "Error: Failed to write file.";
        case ErrorCode::NOTHING_PLAYING: 
            ErrorMessage = "Error: Nothing is currently playing.";
        case ErrorCode::ALREADY_STOPPED: 
            ErrorMessage = "Error: Playback is already stopped.";
        case ErrorCode::EMPTY_PLAYLIST: 
            ErrorMessage = "Error: Playlist is empty.";
        case ErrorCode::INVALID_INPUT: 
            ErrorMessage = "Error: Invalid input.";
        default: 
            ErrorMessage = "Error: Unknown error.";
    }

    return ErrorMessage;
}

#endif
