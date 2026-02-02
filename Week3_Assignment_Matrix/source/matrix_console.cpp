#include <iostream>
#include "matrix_console.h"
#include "validate_input.h"

void getMatrixInput(int** const& matrix, const int& rows, const int& columns)
{
    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            std::cout << "Enter element [" << row << "][" << column << "]: ";
            getValidatedInput(matrix[row][column], 1, 10);
        }
    }
}

void printMatrix(int** const& matrix, const int& rows, const int& columns)
{
    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            std::cout << matrix[row][column] << " ";
        }
        std::cout << '\n';
    }
}
