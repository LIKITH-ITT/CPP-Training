#ifndef MATRIX_TYPES_H
#define MATRIX_TYPES_H

struct MatrixDimensions
{
    int rows;
    int columns;
};

using MatrixOperationFunction = int** (*)(int**, int**, int, int, int, int);

#endif
