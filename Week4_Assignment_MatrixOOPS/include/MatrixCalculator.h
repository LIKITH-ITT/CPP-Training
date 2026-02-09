#ifndef MATRIX_CALCULATOR_H
#define MATRIX_CALCULATOR_H

#include "Matrix.h"

enum class MenuOption
{
    ADDITION = 1,
    MULTIPLICATION,
    EXIT
};

class MatrixCalculator
{
private:
    bool isProgramRunning;

    void displayMenu() const;
    MenuOption getMenuChoice();
    
    void getDimensionsFromConsole(int& rows, int& columns, const char* matrixName);
    void readMatrixFromConsole(Matrix& matrix);
    void printMatrix(const Matrix& matrix) const;
    
    void addMatrix();
    void multiplyMatrix();

public:
    MatrixCalculator();

    void run();
};

#endif
