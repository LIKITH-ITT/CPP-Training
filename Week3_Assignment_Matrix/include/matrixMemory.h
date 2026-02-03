#ifndef MATRIX_MEMORY_H
#define MATRIX_MEMORY_H

int** allocateMatrix(int rows, int columns);

void freeMatrix(int**& matrix, int rows);

#endif
