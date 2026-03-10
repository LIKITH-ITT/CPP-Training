#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "Constants.h"
#include "Logger.h"
#include <string>
#include <algorithm>
#include <fstream>

namespace Validator {

    inline bool isSupportedExtension(const std::string& path) {
        int dotPosition = path.rfind(Constants::FULL_STOP);
        if (dotPosition == std::string::npos) 
        return false;

        std::string extension = path.substr(dotPosition + 1);
        std::transform(extension.begin(), extension.end(), extension.begin(), ::toupper);

        return (extension == Constants::FORMAT_JSON || extension == Constants::FORMAT_CSV || extension == Constants::FORMAT_XML);
    }

    inline bool isValidChoice(const std::string& choice) {
        if (choice.length() != 1 || (choice[0] != Constants::CHOICE_YES && choice[0] != Constants::CHOICE_YES_CAP
            && choice[0] != Constants::CHOICE_NO && choice[0] != Constants::CHOICE_NO_CAP))
        {
            Logger::printMessage(Constants::MSG_INVALID_CHOICE);
            return false;
        }
        return true;
    }

    inline bool isValidFilePath(const std::string& path) {
        if (path.empty())
        {
            Logger::printMessage(Constants::MSG_EMPTY_PATH);
            return false;
        }
        if (!isSupportedExtension(path))
        {
            Logger::printMessage(Constants::MSG_UNSUPPORTED_TYPE);
            return false;
        }
        if (!std::ifstream(path).is_open())
        {
            Logger::printMessage(Constants::MSG_FILE_NOT_FOUND + path);
            Logger::printMessage(Constants::MSG_CHECK_PATH);
            return false;
        }
        return true;
    }

}

#endif
