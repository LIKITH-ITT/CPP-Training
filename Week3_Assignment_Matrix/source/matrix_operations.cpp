#include "matrix_operations.h"
#include "matrix_memory.h"
 
int** addMatrices(int** const& matrixA, int** const& matrixB, const int& rows, const int& columns)
{
    int** resultMatrix = allocateMatrix(rows, columns);

    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            resultMatrix[row][column] = matrixA[row][column] + matrixB[row][column];
        }
    }

    return resultMatrix;
}

int** multiplyMatrices(int** const& matrixA, int** const& matrixB, const int& rows1, const int& columns1, const int& columns2)
{
    int** resultMatrix = allocateMatrix(rows1, columns2);

    for (int resultRow = 0; resultRow < rows1; resultRow++)
    {
        for (int resultColumn = 0; resultColumn < columns2; resultColumn++)
        {
            for (int sumIndex = 0; sumIndex < columns1; sumIndex++)
            {
                resultMatrix[resultRow][resultColumn] += matrixA[resultRow][sumIndex] * matrixB[sumIndex][resultColumn];
            }
        }
    }

    return resultMatrix;
}

int** performAddition(int** const& matrixA, int** const& matrixB, const int& rows1, const int& columns1, const int& rows2, const int& columns2)
{
    return addMatrices(matrixA, matrixB, rows1, columns1);
}

int** performMultiplication(int** const& matrixA, int** const& matrixB, const int& rows1, const int& columns1, const int& rows2, const int& columns2)
{
    return multiplyMatrices(matrixA, matrixB, rows1, columns1, columns2);
}
