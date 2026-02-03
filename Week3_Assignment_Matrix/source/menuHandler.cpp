#include <iostream>
#include "menuHandler.h"
#include "matrixOperations.h"
#include "validateInput.h"

int getMenuChoice()
{
    int menuChoice;
    getValidatedInput(menuChoice, 1, 3);
    
    return menuChoice;
}

void displayMenu()
{
    std::cout << "\n----- Matrix Operations -----\n";
    std::cout << "1. Addition\n";
    std::cout << "2. Multiplication\n";
    std::cout << "3. Exit\n";
    std::cout << "\nEnter choice: ";

    
}

MatrixOperationFunction selectOperation(int menuChoice, bool& shouldContinue)
{
    MatrixOperationFunction selectedOperation = nullptr;

    switch (menuChoice)
    {
        case 1:
            selectedOperation = performAddition;
            break;

        case 2:
            selectedOperation = performMultiplication;
            break;

        case 3:
            shouldContinue = false;
            break;

        default:
            std::cout << "Invalid choice. Please try again.\n";
            shouldContinue = true;
            break;
    }

    return selectedOperation;
}
