#include "Logger.h"
#include <iostream>

void Logger::printMessage(const char* message)
{
    std::cout << message;
}

void Logger::printMessage(const std::string& message)
{
    std::cout << message;
}

std::string Logger::printNextLine()
{
    return "\n";
}
