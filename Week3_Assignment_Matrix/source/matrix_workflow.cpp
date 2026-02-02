#include <iostream>
#include "matrix_workflow.h"
#include "dimension_validator.h"
#include "matrix_memory.h"
#include "matrix_console.h"

void performMatrixOperation(MatrixOperation operation, int operationType)
{
    int rows1, columns1, rows2, columns2;

    bool validDimensions = getDimensionsForOperation(rows1, columns1, rows2, columns2, operationType);
    
    if (!validDimensions) {
        return;
    }

    int** matrixA = allocateMatrix(rows1, columns1);
    int** matrixB = allocateMatrix(rows2, columns2);

    std::cout << "\nEnter Matrix A:\n";
    getMatrixInput(matrixA, rows1, columns1);

    std::cout << "\nEnter Matrix B:\n";
    getMatrixInput(matrixB, rows2, columns2);

    int** resultMatrix = operation(matrixA, matrixB, rows1, columns1, rows2, columns2);

    std::cout << "\nResult Matrix:\n";
    if (operationType == 1)
        printMatrix(resultMatrix, rows1, columns1);
    else
        printMatrix(resultMatrix, rows1, columns2);

    freeMatrix(resultMatrix, rows1);
    freeMatrix(matrixA, rows1);
    freeMatrix(matrixB, rows2);
}
