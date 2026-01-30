#include "matrix_memory.h"

int** allocateMatrix(const int& rows, const int& columns)
{
    int** matrix = new int*[rows]();
    for (int row = 0; row < rows; row++)
    {
        matrix[row] = new int[columns]();
    }
    return matrix;
}

void freeMatrix(int**& matrix, const int& rows)
{
    if (matrix == nullptr)
        return;

    for (int row = 0; row < rows; row++)
    {
        delete[] matrix[row];
    }
    delete[] matrix;
    matrix = nullptr; 
}
