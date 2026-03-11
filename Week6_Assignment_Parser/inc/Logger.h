#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger
{
public:
    static void printMessage(const char* message);
    static void printMessage(const std::string& message);
    static std::string printNextLine();

    ~Logger() {}
};

#endif
