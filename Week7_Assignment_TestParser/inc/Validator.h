#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "Logger.h"
#include <string>

class Validator
{
public:

    static bool isValidFilePath(const std::string& filePath);
    static bool isValidChoice(const std::string& input);
    static std::string extractExtension(const std::string& filePath);


    ~Validator() {}

private:
    static bool isPathNonEmpty(const std::string& filePath);
    static bool hasSupportedExtension(const std::string& filePath);
    static bool isFileAccessible(const std::string& filePath);
    static std::string toUpperCase(const std::string& input);
};

#endif
