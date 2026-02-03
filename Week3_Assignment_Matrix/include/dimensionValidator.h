#ifndef DIMENSION_VALIDATOR_H
#define DIMENSION_VALIDATOR_H

#include "matrixTypes.h"

bool validateAdditionDimensions(const MatrixDimensions& firstMatrix, const MatrixDimensions& secondMatrix);

bool validateMultiplicationDimensions(const MatrixDimensions& firstMatrix, const MatrixDimensions& secondMatrix);

#endif
