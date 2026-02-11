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

    void displayMenu();
    MenuOption getMenuChoice();
    
    void getDimensionsFromConsole(int& rows, int& columns, const char* matrixName);
    void readMatrixFromConsole(Matrix& matrix);
    void printMatrix(Matrix& matrix);
    
    void addMatrix();
    void multiplyMatrix();

public:
    MatrixCalculator();

    void run();
};

#endif
