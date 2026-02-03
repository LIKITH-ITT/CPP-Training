#include <iostream>
#include "dimensionUI.h"
#include "dimensionValidator.h"
#include "validateInput.h"

void displayDimensionMismatchError(const MatrixDimensions& firstMatrix, const MatrixDimensions& secondMatrix, int operationType)
{
    if (operationType == 1)
    {
        std::cout << "*****************************************************";
        std::cout << "\nAddition requires matrices with identical dimensions.\n";
        std::cout << "Matrix A is " << firstMatrix.rows << "x" << firstMatrix.columns 
                  << " but Matrix B is " << secondMatrix.rows << "x" << secondMatrix.columns << "\n";
        std::cout << "Please try again with matching dimensions.\n";
        std::cout << "*****************************************************\n";
    }
    else if (operationType == 2)
    {
        std::cout << "********************************************************************";
        std::cout << "\nFor multiplication, columns of Matrix A must equal rows of Matrix B.\n";
        std::cout << "Matrix A has " << firstMatrix.columns << " columns but Matrix B has " 
                  << secondMatrix.rows << " rows.\n";
        std::cout << "Please try again with compatible dimensions.\n";
        std::cout << "********************************************************************\n";
    }
}

bool getDimensionsForOperation(MatrixDimensions& firstMatrix, MatrixDimensions& secondMatrix, int operationType)
{
    std::cout << "\nEnter rows of Matrix A: ";
    getValidatedInput(firstMatrix.rows, 1, 10);

    std::cout << "Enter columns of Matrix A: ";
    getValidatedInput(firstMatrix.columns, 1, 10);

    std::cout << "\nEnter rows of Matrix B: ";
    getValidatedInput(secondMatrix.rows, 1, 10);

    std::cout << "Enter columns of Matrix B: ";
    getValidatedInput(secondMatrix.columns, 1, 10);

    bool isValid = false;

    if (operationType == 1)
    {
        isValid = validateAdditionDimensions(firstMatrix, secondMatrix);
    }
    else if (operationType == 2)
    {
        isValid = validateMultiplicationDimensions(firstMatrix, secondMatrix);
    }

    if (!isValid)
    {
        displayDimensionMismatchError(firstMatrix, secondMatrix, operationType);
        return false;
    }

    return true;
}
