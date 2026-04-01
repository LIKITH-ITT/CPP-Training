#include "Validator.h"
#include "Logger.h"
#include <iostream>
#include <limits>

bool Validator::hasExtraCharactersInInput()
{
    char bufferCharacter;

    while (std::cin.get(bufferCharacter) && bufferCharacter != '\n')
    {
        if (bufferCharacter != ' ' && bufferCharacter != '\t')
            return true;
    }

    return false;
}

void Validator::getValidatedInput(int& value, int minimumValue, int maximumValue)
{
    while (true)
    {
        std::cin >> value;

        if (!std::cin.fail() && value >= minimumValue && value <= maximumValue)
        {
            if (!hasExtraCharactersInInput())
                return;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << Logger::ERROR_INVALID_INPUT << minimumValue << " and " << maximumValue << ": ";
    }
}
