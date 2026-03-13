#include "Validator.h"
#include "Constants.h"
#include <fstream>


std::string Validator::toUpperCase(const std::string& input)
{
    std::string result = input;

    for (char& character : result)
    {
        if (character >= 'a' && character <= 'z')
        {
            character = character - ('a' - 'A');
        }
    }

    return result;
}
std::string Validator::extractExtension(const std::string& filePath)
{
    std::string   extension;
    size_t dotPosition = filePath.rfind(Constants::FULL_STOP);

    if (dotPosition != std::string::npos)
    {
        extension = toUpperCase(filePath.substr(dotPosition + 1));
    }

    return extension;
}

bool Validator::isPathNonEmpty(const std::string& filePath)
{
    bool result = !filePath.empty();

    if (!result)
    {
        Logger::printMessage(Constants::MSG_EMPTY_PATH);
    }

    return result;
}

bool Validator::hasSupportedExtension(const std::string& filePath)
{
    std::string extension = extractExtension(filePath);

    bool result = (extension == Constants::FORMAT_JSON ||
                   extension == Constants::FORMAT_CSV  ||
                   extension == Constants::FORMAT_XML);

    if (!result)
    {
        Logger::printMessage(Constants::MSG_UNSUPPORTED_TYPE);
    }

    return result;
}

bool Validator::isFileAccessible(const std::string& filePath)
{
    std::ifstream file(filePath);
    bool          result = file.is_open();

    if (!result)
    {
        Logger::printMessage(Constants::MSG_FILE_NOT_FOUND + filePath);
        Logger::printMessage(Constants::MSG_CHECK_PATH);
    }

    return result;
}


bool Validator::isValidFilePath(const std::string& filePath)
{
    bool result = isPathNonEmpty(filePath)        &&
                  hasSupportedExtension(filePath) &&
                  isFileAccessible(filePath);

    return result;
}

bool Validator::isValidChoice(const std::string& input)
{
    bool isCorrectLength   = (input.length() == 1);
    bool isAcceptedCharacter = false;

    if (isCorrectLength)
    {
        isAcceptedCharacter = (input[0] == Constants::CHOICE_YES     ||
                               input[0] == Constants::CHOICE_YES_CAP ||
                               input[0] == Constants::CHOICE_NO      ||
                               input[0] == Constants::CHOICE_NO_CAP);
    }

    bool result = (isCorrectLength && isAcceptedCharacter);

    if (!result)
    {
        Logger::printMessage(Constants::MSG_INVALID_CHOICE);
    }

    return result;
}
