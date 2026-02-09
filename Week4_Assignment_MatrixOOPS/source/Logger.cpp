#include "Logger.h"
#include <iostream>

const std::string Logger::MENU_DISPLAY =
    "\n----- Matrix Operations -----\n"
    "1. Addition\n"
    "2. Multiplication\n"
    "3. Exit\n"
    "\nEnter choice: ";

const std::string Logger::PROMPT_ROWS = "Enter rows of Matrix ";
const std::string Logger::PROMPT_COLUMNS = "Enter columns of Matrix ";
const std::string Logger::PROMPT_ELEMENT = "Enter element ";
const std::string Logger::PROMPT_ENTER_MATRIX_A = "\nEnter Matrix A:";
const std::string Logger::PROMPT_ENTER_MATRIX_B = "\nEnter Matrix B:";
const std::string Logger::RESULT_MATRIX_LABEL = "\nResult Matrix:";

const std::string Logger::ERROR_ADDITION_DIMENSION = "Addition requires matrices with identical dimensions.";
const std::string Logger::ERROR_MULTIPLICATION_DIMENSION = "For multiplication, columns of Matrix A must equal rows of Matrix B.";
const std::string Logger::ERROR_INVALID_INPUT = "***Invalid input. Enter a value again between ";

const std::string Logger::EXIT_MESSAGE = "\nProgram exited successfully.";

const int Logger::MIN_DIMENSION = 1;
const int Logger::MAX_DIMENSION = 10;
const int Logger::MIN_ELEMENT_VALUE = 1;
const int Logger::MAX_ELEMENT_VALUE = 10;
const int Logger::MIN_MENU_CHOICE = 1;
const int Logger::MAX_MENU_CHOICE = 3;

void Logger::printMenu()
{
    std::cout << MENU_DISPLAY;
}

void Logger::printExitMessage()
{
    std::cout << EXIT_MESSAGE << '\n';
}

void Logger::printMatrixPrompt(const std::string& matrixName)
{
    if (matrixName == "A")
    {
        std::cout << PROMPT_ENTER_MATRIX_A << '\n';
    }
    else if (matrixName == "B")
    {
        std::cout << PROMPT_ENTER_MATRIX_B << '\n';
    }
}

void Logger::printResultLabel()
{
    std::cout << RESULT_MATRIX_LABEL << '\n';
}

void Logger::printAdditionError(int rows1, int cols1, int rows2, int cols2)
{
    std::cout << "********************************************************************\n";
    std::cout << ERROR_ADDITION_DIMENSION << '\n';
    std::cout << "Matrix A is " << rows1 << "x" << cols1
              << " but Matrix B is " << rows2 << "x" << cols2 << '\n';
    std::cout << "Please try again with matching dimensions.\n";
    std::cout << "********************************************************************\n";
}

void Logger::printMultiplicationError(int cols1, int rows2)
{
    std::cout << "********************************************************************\n";
    std::cout << ERROR_MULTIPLICATION_DIMENSION << '\n';
    std::cout << "Matrix A has " << cols1 << " columns but Matrix B has "
              << rows2 << " rows.\n";
    std::cout << "Please try again with compatible dimensions.\n";
    std::cout << "********************************************************************\n";
}
