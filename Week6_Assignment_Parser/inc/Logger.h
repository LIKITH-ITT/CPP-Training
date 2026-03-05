#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <iomanip>
#include <string>

namespace Logger {

    inline void printMessage(const char* message) {
        std::cout << message;
    }

    inline void printMessage(const std::string& message) {
        std::cout << message;
    }

    inline std::string printNextLine(){
        return "\n";
    }
}

#endif
