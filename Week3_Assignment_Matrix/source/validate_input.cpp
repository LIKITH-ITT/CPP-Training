#include <iostream>
#include "validate_input.h"

bool hasExtraCharactersInInput()
{
    char bufferCharacter;

    while (std::cin.get(bufferCharacter) && bufferCharacter != '\n')
    {
        if (bufferCharacter != ' ' && bufferCharacter != '\t')
            return true;   
    }

    return false;
}

void getValidatedInput(int& value, int min, int max)
{
    while (true)
    {
        std::cin >> value;

        if (!std::cin.fail() && value >= min && value <= max)
        {
            if (!hasExtraCharactersInInput())
                return; 
        }

        std::cin.clear();
        std::cin.ignore(1000, '\n');

        std::cout << "Invalid input. Enter a value again between " << min << " and " << max << ": ";
    }
}
