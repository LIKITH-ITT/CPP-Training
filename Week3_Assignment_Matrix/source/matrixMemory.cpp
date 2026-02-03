#include "matrixMemory.h"

int** allocateMatrix(int rows, int columns)
{
    int** matrix = new int*[rows]();
    
    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        matrix[rowIndex] = new int[columns]();
    }
    
    return matrix;
}

void freeMatrix(int**& matrix, int rows)
{
    if (matrix == nullptr)
        return;

    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        delete[] matrix[rowIndex];
    }
    
    delete[] matrix;
    matrix = nullptr;
}
