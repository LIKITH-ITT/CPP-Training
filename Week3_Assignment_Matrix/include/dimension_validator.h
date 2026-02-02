#ifndef DIMENSION_VALIDATOR_H
#define DIMENSION_VALIDATOR_H

bool getDimensionsForOperation(int& rows1, int& cols1, int& rows2, int& cols2, int operationType);

bool validateAdditionDimensions(int rows1, int cols1, int rows2, int cols2);

bool validateMultiplicationDimensions(int cols1, int rows2);

#endif
