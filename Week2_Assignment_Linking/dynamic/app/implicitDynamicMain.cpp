#include <iostream>
#include "add.h"
#include "subtract.h"
#include "multiply.h"
#include "divide.h"


int main() {

    int firstNumber = 0;
    int secondNumber = 0;
    int menuChoice;
    bool loopRunning = true;

    while (loopRunning) {
        std::cout << "\n-----------Implicit Dynamic Linking-----------\n";

        std::cout << "\nChoose operation:\n";
        std::cout << "1. Addition\n";
        std::cout << "2. Subtraction\n";
        std::cout << "3. Multiplication\n";
        std::cout << "4. Division\n";
        std::cout << "5. Exit the program\n";
        std::cout << "Enter choice (1-5): ";
        std::cin >> menuChoice;

        if(menuChoice == 5){
            std::cout << "Exiting the program...\n";
            loopRunning = false;
            break;
        }

        std::cout << "Enter two integers: ";
        std::cin >> firstNumber >> secondNumber;     

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (menuChoice) {
            case 1:
                std::cout << "\nResult: " << add(firstNumber, secondNumber) << '\n';
                break;

            case 2:
                std::cout << "\nResult: " << subtract(firstNumber, secondNumber)  << '\n';
                break;

            case 3:
                std::cout << "\nResult: " << multiply(firstNumber, secondNumber)  << '\n';
                break;

            case 4:
                if (secondNumber == 0) {
                    std::cout << "\nError: Division by zero\n";
                } else {
                    std::cout << "\nResult: " << divide(firstNumber, secondNumber)  << '\n';
                }
                break;

            default:
                std::cout << "\nInvalid choice\n";
            }
        }        

    return 0;
}
