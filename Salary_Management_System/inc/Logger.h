#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <iomanip>
#include <string>
#include "UIStrings.h"

namespace Logger 
{
    inline void info(const std::string& message) 
    {
        std::cout << "\n[INFO] " << message << std::endl;
    }

    inline void warning(const std::string& message) 
    {
        std::cout << "\n[WARNING] " << message << std::endl;
    }

}

#endif
