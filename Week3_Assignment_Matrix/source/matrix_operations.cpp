#include <iostream>
#include "matrix_operations.h"
#include "matrix_memory.h"
 
int** addMatrices(int** const& matrixA, int** const& matrixB, const int& rows, const int& columns)
{
    int** resultMatrix = allocateMatrix(rows, columns);

    for (int row = 0; row < rows; row++)
        for (int column = 0; column < columns; column++)
        {
            resultMatrix[row][column] = matrixA[row][column] + matrixB[row][column];
        }

    return resultMatrix;
}

int** multiplyMatrices(int** const& matrixA, int** const& matrixB, const int& rows1, const int& columns1, const int& columns2)
{
    int** resultMatrix = allocateMatrix(rows1, columns2);

    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < columns2; j++)
        {
            for (int k = 0; k < columns1; k++)
            {
                resultMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    return resultMatrix;
}

int** performAddition(int** const& matrixA, int** const& matrixB, const int& rows1, const int& columns1, const int& rows2, const int& columns2)
{
    if (rows1 != rows2 || columns1 != columns2)
    {
        std::cout << "Addition not possible (dimension mismatch)\n";
        return nullptr;
    }

    return addMatrices(matrixA, matrixB, rows1, columns1);
}

int** performMultiplication(int** const& matrixA, int** const& matrixB, const int& rows1, const int& columns1, const int& rows2, const int& columns2)
{
    if (columns1 != rows2)
    {
        std::cout << "Multiplication not possible as column1 and row2 does not match\n";
        return nullptr;
    }

    return multiplyMatrices(matrixA, matrixB, rows1, columns1, columns2);
}
