#include <iostream>
#include "matrixConsole.h"
#include "validateInput.h"

void getMatrixInput(int** matrix, int rows, int columns)
{
    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < columns; columnIndex++)
        {
            std::cout << "Enter element [" << rowIndex << "][" << columnIndex << "]: ";
            getValidatedInput(matrix[rowIndex][columnIndex], 1, 10);
        }
    }
}

void printMatrix(int** matrix, int rows, int columns)
{
    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < columns; columnIndex++)
        {
            std::cout << matrix[rowIndex][columnIndex] << " ";
        }
        std::cout << '\n';
    }
}
