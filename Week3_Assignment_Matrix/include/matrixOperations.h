#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

int** addMatrices(int** firstMatrix, int** secondMatrix, int rows, int columns);

int** multiplyMatrices(int** firstMatrix, int** secondMatrix, int firstRows, int firstColumns, int secondColumns);

int** performAddition(int** firstMatrix, int** secondMatrix, int firstRows, int firstColumns, int secondRows, int secondColumns);

int** performMultiplication(int** firstMatrix, int** secondMatrix, int firstRows, int firstColumns, int secondRows, int secondColumns);

#endif
