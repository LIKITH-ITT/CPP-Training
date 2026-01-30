#include <iostream>
#include "validate_input.h"

void getValidatedInput(int& value, int min, int max)
{
    while (true)
    {
        std::cin >> value;

        if (!std::cin.fail() && value >= min && value <= max)
            return;

        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input. Enter a value again between " << min << " and " << max << ": ";
    }
}
