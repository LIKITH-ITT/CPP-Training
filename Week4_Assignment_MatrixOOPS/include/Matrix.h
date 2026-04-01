#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
private:
    int rows;
    int columns;
    int** matrixElements;

    void allocateMemory();
    void deallocateMemory();

public:
    Matrix(int rows, int columns);
    Matrix(const Matrix& other);
    ~Matrix();

    int getRows();
    int getColumns();
    int** getMatrixElements();

    Matrix operator+(Matrix& other);
    
    Matrix operator*(Matrix& other);
    
    Matrix& operator=(Matrix& other);

};

#endif
