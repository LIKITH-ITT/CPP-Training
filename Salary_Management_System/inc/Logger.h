#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>

namespace Logger 
{

    inline void log(const std::string& message) 
    {
        std::cout << "\n[LOG] " << message << std::endl;
    }

    inline void info(const std::string& message) 
    {
        std::cout << "\n[INFO] " << message << std::endl;
    }

    inline void warning(const std::string& message) 
    {
        std::cout << "\n[WARNING] " << message << std::endl;
    }

    inline void error(const std::string& message) 
    {
        std::cerr << "\n[ERROR] " << message << std::endl;
    }

}

#endif
