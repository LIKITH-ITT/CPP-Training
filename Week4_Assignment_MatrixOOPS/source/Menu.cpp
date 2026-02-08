#include <iostream>
#include "Menu.h"
#include "MatrixCalculator.h"
#include "InputValidator.h"

Menu::Menu() : isProgramRunning(true)
{
}

void Menu::displayOptions() const
{
    std::cout << "\n----- Matrix Operations -----\n";
    std::cout << "1. Addition\n";
    std::cout << "2. Multiplication\n";
    std::cout << "3. Exit\n";
    std::cout << "\nEnter choice: ";
}

int Menu::getChoice()
{
    int menuChoice;
    InputValidator::getValidatedInput(menuChoice, 1, 3);
    
    return menuChoice;
}

void Menu::run()
{
    MatrixCalculator calculator;

    while (isProgramRunning)
    {
        displayOptions();
        int menuChoice = getChoice();
        
        switch (menuChoice)
        {
            case 1:
            case 2:
                calculator.executeOperation(menuChoice);
                break;

            case 3:
                isProgramRunning = false;
                break;

            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    std::cout << "\nProgram exited successfully.\n";
}
