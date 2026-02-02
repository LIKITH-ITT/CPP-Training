#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

int** addMatrices(int** const& matrixA, int** const& matrixB, const int& rows, const int& columns);
int** multiplyMatrices(int** const& matrixA, int** const& matrixB, const int& rows1, const int& columns1, const int& columns2);

int** performAddition(int** const& matrixA, int** const& matrixB, const int& rows1, const int& columns1, const int& rows2, const int& columns2);
int** performMultiplication(int** const& matrixA, int** const& matrixB, const int& rows1, const int& columns1, const int& rows2, const int& columns2);

#endif
