#ifndef MATRIX_MEMORY_H
#define MATRIX_MEMORY_H

int** allocateMatrix(const int& rows, const int& columns);

void freeMatrix(int**& matrix, const int& rows);
 
#endif
