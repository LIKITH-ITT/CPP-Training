#include "matrixOperations.h"
#include "matrixMemory.h"

int** addMatrices(int** firstMatrix, int** secondMatrix, int rows, int columns)
{
    int** resultMatrix = allocateMatrix(rows, columns);

    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < columns; columnIndex++)
        {
            resultMatrix[rowIndex][columnIndex] = firstMatrix[rowIndex][columnIndex] + secondMatrix[rowIndex][columnIndex];
        }
    }

    return resultMatrix;
}

int** multiplyMatrices(int** firstMatrix, int** secondMatrix, int firstRows, int firstColumns, int secondColumns)
{
    int** resultMatrix = allocateMatrix(firstRows, secondColumns);

    for (int resultRowIndex = 0; resultRowIndex < firstRows; resultRowIndex++)
    {
        for (int resultColumnIndex = 0; resultColumnIndex < secondColumns; resultColumnIndex++)
        {
            for (int sumIndex = 0; sumIndex < firstColumns; sumIndex++)
            {
                resultMatrix[resultRowIndex][resultColumnIndex] += firstMatrix[resultRowIndex][sumIndex] * secondMatrix[sumIndex][resultColumnIndex];
            }
        }
    }

    return resultMatrix;
}

int** performAddition(int** firstMatrix, int** secondMatrix, int firstRows, int firstColumns, int secondRows, int secondColumns)
{
    (void)secondRows;
    (void)secondColumns;
    return addMatrices(firstMatrix, secondMatrix, firstRows, firstColumns);
}

int** performMultiplication(int** firstMatrix, int** secondMatrix, int firstRows, int firstColumns, int secondRows, int secondColumns)
{
    (void)secondRows;
    return multiplyMatrices(firstMatrix, secondMatrix, firstRows, firstColumns, secondColumns);
}
