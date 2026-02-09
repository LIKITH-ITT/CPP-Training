#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix
{
private:
    int rows;
    int columns;
    int** data;

    void allocateMemory();
    void deallocateMemory();
    void initializeToZero();

public:
    Matrix(int rows, int columns);
    Matrix(const Matrix& other);
    ~Matrix();

    int getRows() const;
    int getColumns() const;
    int** getData() const;

    void inputFromConsole();
    void displayToConsole() const;

    Matrix add(const Matrix& other) const;
    Matrix multiply(const Matrix& other) const;

    bool canAddWith(const Matrix& other) const;
    bool canMultiplyWith(const Matrix& other) const;
};

#endif
