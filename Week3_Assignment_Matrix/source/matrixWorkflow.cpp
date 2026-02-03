#include <iostream>
#include "matrixWorkflow.h"
#include "dimensionUI.h"
#include "matrixMemory.h"
#include "matrixConsole.h"

void performMatrixOperation(MatrixOperationFunction operation, int operationType)
{
    MatrixDimensions firstMatrix;
    MatrixDimensions secondMatrix;

    bool validDimensions = getDimensionsForOperation(firstMatrix, secondMatrix, operationType);
    
    if (!validDimensions)
    {
        return;
    }

    int** matrixA = allocateMatrix(firstMatrix.rows, firstMatrix.columns);
    int** matrixB = allocateMatrix(secondMatrix.rows, secondMatrix.columns);

    std::cout << "\nEnter Matrix A:\n";
    getMatrixInput(matrixA, firstMatrix.rows, firstMatrix.columns);

    std::cout << "\nEnter Matrix B:\n";
    getMatrixInput(matrixB, secondMatrix.rows, secondMatrix.columns);

    int** resultMatrix = operation(matrixA, matrixB, firstMatrix.rows, firstMatrix.columns, secondMatrix.rows, secondMatrix.columns);

    std::cout << "\nResult Matrix:\n";
    
    if (operationType == 1)
    {
        printMatrix(resultMatrix, firstMatrix.rows, firstMatrix.columns);
    }
    else
    {
        printMatrix(resultMatrix, firstMatrix.rows, secondMatrix.columns);
    }

    freeMatrix(resultMatrix, firstMatrix.rows);
    freeMatrix(matrixA, firstMatrix.rows);
    freeMatrix(matrixB, secondMatrix.rows);
}
