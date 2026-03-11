#ifndef UTILITY_H
#define UTILITY_H

#include "Logger.h"
#include "Validator.h"
#include <string>

class Utility
{
public:
    static std::string getFilePath();
    static char getUserChoice();

    ~Utility() {}

private:
    static std::string readLine();
};

#endif
