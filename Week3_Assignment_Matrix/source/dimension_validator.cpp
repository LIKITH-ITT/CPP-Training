#include <iostream>
#include "dimension_validator.h"
#include "validate_input.h"

bool validateAdditionDimensions(int rows1, int cols1, int rows2, int cols2)
{
    return (rows1 == rows2 && cols1 == cols2);
}

bool validateMultiplicationDimensions(int cols1, int rows2)
{
    return (cols1 == rows2);
}

bool getDimensionsForOperation(int& rows1, int& cols1, int& rows2, int& cols2, int operationType)
{
    std::cout << "\nEnter rows of Matrix A: ";
    getValidatedInput(rows1, 1, 10);

    std::cout << "Enter columns of Matrix A: ";
    getValidatedInput(cols1, 1, 10);

    std::cout << "\nEnter rows of Matrix B: ";
    getValidatedInput(rows2, 1, 10);

    std::cout << "Enter columns of Matrix B: ";
    getValidatedInput(cols2, 1, 10);

    if (operationType == 1)
    {
        if (!validateAdditionDimensions(rows1, cols1, rows2, cols2))
        {
            std::cout << "*****************************************************";
            std::cout << "\nAddition requires matrices with identical dimensions.\n";
            std::cout << "Matrix A is " << rows1 << "x" << cols1 << " but Matrix B is " << rows2 << "x" << cols2 << "\n";
            std::cout << "Please try again with matching dimensions.\n";
            std::cout << "*****************************************************\n";
            return false;
        }
    }
    else if (operationType == 2)
    {
        if (!validateMultiplicationDimensions(cols1, rows2))
        {
            std::cout << "********************************************************************";
            std::cout << "\nFor multiplication, columns of Matrix A must equal rows of Matrix B.\n";
            std::cout << "Matrix A has " << cols1 << " columns but Matrix B has " << rows2 << " rows.\n";
            std::cout << "Please try again with compatible dimensions.\n";
            std::cout << "********************************************************************\n";
            return false;
        }
    }

    return true;
}
