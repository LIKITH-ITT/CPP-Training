#include <iostream>
#include "menu_handler.h"
#include "validate_input.h"

int displayMenuAndGetChoice()
{
    std::cout << "\n----- Matrix Operations -----\n";
    std::cout << "1. Addition\n";
    std::cout << "2. Multiplication\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter choice: ";

    int menuChoice;
    getValidatedInput(menuChoice, 1, 3);
    
    return menuChoice;
}

MatrixOperation selectOperation(const int menuChoice, bool& shouldContinue)
{
    MatrixOperation selectedOperation = nullptr;

    switch (menuChoice)
    {
        case 1:
            selectedOperation = performAddition;
            break;

        case 2:
            selectedOperation = performMultiplication;
            break;

        case 3:
            //shouldExit = true;
            shouldContinue = false;
            break;

        default:
            std::cout << "Invalid choice. Please try again.\n";
            shouldContinue = true;
            break;
    }

    return selectedOperation;
}
