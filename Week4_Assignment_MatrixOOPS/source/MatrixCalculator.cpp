#include <iostream>
#include "MatrixCalculator.h"

bool MatrixCalculator::getDimensionsForOperation(MatrixDimension& firstDimension, MatrixDimension& secondDimension, int operationType)
{
    firstDimension.inputFromConsole("A");
    secondDimension.inputFromConsole("B");

    bool isValid = false;

    if (operationType == 1)
    {
        isValid = firstDimension.isValidForAddition(secondDimension);
        if (!isValid)
        {
            firstDimension.displayAdditionMismatchError(secondDimension);
        }
    }
    else if (operationType == 2)
    {
        isValid = firstDimension.isValidForMultiplication(secondDimension);
        if (!isValid)
        {
            firstDimension.displayMultiplicationMismatchError(secondDimension);
        }
    }

    return isValid;
}

void MatrixCalculator::performAdditionOperation()
{
    MatrixDimension firstDimension;
    MatrixDimension secondDimension;

    bool validDimensions = getDimensionsForOperation(firstDimension, secondDimension, 1);
    
    if (!validDimensions)
    {
        return;
    }

    Matrix matrixA(firstDimension.getRows(), firstDimension.getColumns());
    Matrix matrixB(secondDimension.getRows(), secondDimension.getColumns());

    std::cout << "\nEnter Matrix A:\n";
    matrixA.inputFromConsole();

    std::cout << "\nEnter Matrix B:\n";
    matrixB.inputFromConsole();

    Matrix resultMatrix = matrixA.add(matrixB);

    std::cout << "\nResult Matrix:\n";
    resultMatrix.displayToConsole();
}

void MatrixCalculator::performMultiplicationOperation()
{
    MatrixDimension firstDimension;
    MatrixDimension secondDimension;

    bool validDimensions = getDimensionsForOperation(firstDimension, secondDimension, 2);
    
    if (!validDimensions)
    {
        return;
    }

    Matrix matrixA(firstDimension.getRows(), firstDimension.getColumns());
    Matrix matrixB(secondDimension.getRows(), secondDimension.getColumns());

    std::cout << "\nEnter Matrix A:\n";
    matrixA.inputFromConsole();

    std::cout << "\nEnter Matrix B:\n";
    matrixB.inputFromConsole();

    Matrix resultMatrix = matrixA.multiply(matrixB);

    std::cout << "\nResult Matrix:\n";
    resultMatrix.displayToConsole();
}

void MatrixCalculator::executeOperation(int operationType)
{
    switch (operationType)
    {
        case 1:
            performAdditionOperation();
            break;

        case 2:
            performMultiplicationOperation();
            break;

        default:
            break;
    }
}
