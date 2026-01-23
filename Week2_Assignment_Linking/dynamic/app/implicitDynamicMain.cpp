#include <iostream>
#include "add.h"
#include "subtract.h"
#include "multiply.h"
#include "divide.h"

int main() 
{
    double firstOperand = 0;
    double secondOperand = 0;
    int menuChoice;
    bool isLoopRunning = true;

    while (isLoopRunning) 
    {
        std::cout << "\n-----------Implicit Dynamic Linking-----------\n";

        std::cout << "\nChoose operation:\n";
        std::cout << "1. Addition\n";
        std::cout << "2. Subtraction\n";
        std::cout << "3. Multiplication\n";
        std::cout << "4. Division\n";
        std::cout << "5. Exit the program\n";
        std::cout << "Enter choice (1-5): ";
        std::cin >> menuChoice;

        if (std::cin.fail()) 
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "\nInvalid input. Please enter a number.\n";
            continue;
        }

        if(menuChoice == 5)
        {
            std::cout << "Exiting the program...\n";
            isLoopRunning = false;
            break;
        }

        if(menuChoice <1 || menuChoice > 5)
        {
        std::cout << "\nInvalid choice\n";
        continue;
        }
        
        std::cout << "Enter the first operand:";
        std::cin >> firstOperand; 
        std::cout << "Enter the second operand:";  
        std::cin >> secondOperand; 

        if (std::cin.fail()) 
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "\nInvalid input. Please enter a number(1 - 5).\n";
            continue;
        }

        switch (menuChoice) 
        {
            case 1:
                std::cout << "\nResult: " << add(firstOperand, secondOperand) << '\n';
                break;

            case 2:
                std::cout << "\nResult: " << subtract(firstOperand, secondOperand)  << '\n';
                break;

            case 3:
                std::cout << "\nResult: " << multiply(firstOperand, secondOperand)  << '\n';
                break;

            case 4:
                if (secondOperand == 0) 
                {
                    std::cout << "\nError: Division by zero\n";
                } 
                else 
                {
                    std::cout << "\nResult: " << divide(firstOperand, secondOperand)  << '\n';
                }
                break;
        }
    } 

    return 0;
}
