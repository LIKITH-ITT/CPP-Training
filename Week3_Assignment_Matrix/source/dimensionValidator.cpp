#include "dimensionValidator.h"

bool validateAdditionDimensions(const MatrixDimensions& firstMatrix, const MatrixDimensions& secondMatrix)
{
    return (firstMatrix.rows == secondMatrix.rows && firstMatrix.columns == secondMatrix.columns);
}

bool validateMultiplicationDimensions(const MatrixDimensions& firstMatrix, const MatrixDimensions& secondMatrix)
{
    return (firstMatrix.columns == secondMatrix.rows);
}
