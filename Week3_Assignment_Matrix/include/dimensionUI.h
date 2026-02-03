#ifndef DIMENSION_UI_H
#define DIMENSION_UI_H

#include "matrixTypes.h"

bool getDimensionsForOperation(MatrixDimensions& firstMatrix, MatrixDimensions& secondMatrix, int operationType);

void displayDimensionMismatchError(const MatrixDimensions& firstMatrix, const MatrixDimensions& secondMatrix, int operationType);

#endif
