#ifndef MATRIX_CALCULATOR_H
#define MATRIX_CALCULATOR_H

#include "Matrix.h"
#include "MatrixDimension.h"

class MatrixCalculator
{
private:
    void performAdditionOperation();
    void performMultiplicationOperation();
    
    bool getDimensionsForOperation(MatrixDimension& firstDimension, MatrixDimension& secondDimension, int operationType);

public:
    void executeOperation(int operationType);
};

#endif
