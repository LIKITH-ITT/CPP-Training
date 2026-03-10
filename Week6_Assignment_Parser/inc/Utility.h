#ifndef UTILITY_H
#define UTILITY_H

#include "Constants.h"
#include "Logger.h"
#include "Validator.h"
#include <iostream>
#include <string>

namespace Utility {

    inline char getUserChoice() {
        std::string choice;
        while (true)
        {
            Logger::printMessage(Constants::MSG_CONTINUE);
            std::getline(std::cin, choice);
            if (Validator::isValidChoice(choice)) 
                break;
        }
        return choice[0];
    }

    inline std::string getFilePath() {
        std::string path;
        while (true)
        {
            Logger::printMessage(Constants::MSG_ENTER_FILE_PATH);
            std::getline(std::cin, path);
            if (Validator::isValidFilePath(path)) 
                break;
        }
        return path;
    }

}

#endif
