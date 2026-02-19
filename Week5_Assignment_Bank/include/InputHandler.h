#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <iostream>
#include <limits>
#include<UIStrings.h>

namespace InputHandler
{
    int getIntInput()
    {
        int input;

        while (true)
        {
            if (std::cin >> input)
            {
                if (std::cin.peek() == '\n')
                {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    return input;
                }
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << UIStrings::INVALID_INPUT;
            std::cout << UIStrings::PROMPT_AGAIN;
        }
    }

    double getDoubleInput()
    {
        double input;

        while (true)
        {
            if (std::cin >> input)
            {
                if (std::cin.peek() == '\n')
                {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if (input > 0)
                        return input;
                }
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << UIStrings::INVALID_INPUT;
            std::cout << UIStrings::PROMPT_AGAIN;
        }
    }
}

#endif