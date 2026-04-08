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

inline std::string errorToString(ErrorCode errorCode)
{
    std::string ErrorMessage;
    switch (errorCode)
    {
        case ErrorCode::SUCCESS: 
            ErrorMessage = "Success.";
            break;
        case ErrorCode::PLAYLIST_ALREADY_EXISTS: 
            ErrorMessage = "Error: Playlist already exists.";
            break;
        case ErrorCode::PLAYLIST_NOT_FOUND: 
            ErrorMessage = "Error: Playlist not found.";
            break;
        case ErrorCode::SONG_NOT_FOUND: 
            ErrorMessage = "Error: Song not found.";
            break;
        case ErrorCode::INVALID_INDEX: 
            ErrorMessage = "Error: Invalid song index.";
            break;
        case ErrorCode::FILE_NOT_FOUND: 
            ErrorMessage = "Error: File not found.";
            break;
        case ErrorCode::FILE_READ_ERROR: 
            ErrorMessage = "Error: Failed to read file.";
            break;
        case ErrorCode::FILE_WRITE_ERROR: 
            ErrorMessage = "Error: Failed to write file.";
            break;
        case ErrorCode::NOTHING_PLAYING: 
            ErrorMessage = "Error: Nothing is currently playing.";
            break;
        case ErrorCode::ALREADY_STOPPED: 
            ErrorMessage = "Error: Playback is already stopped.";
            break;
        case ErrorCode::EMPTY_PLAYLIST: 
            ErrorMessage = "Error: Playlist is empty.";
            break;
        case ErrorCode::INVALID_INPUT: 
            ErrorMessage = "Error: Invalid input.";
            break;
        default: 
            ErrorMessage = "Error: Unknown error.";
    }

    return ErrorMessage;
}

#endif
