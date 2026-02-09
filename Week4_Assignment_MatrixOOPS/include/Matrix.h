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

    int getRows() const;
    int getColumns() const;
    int** getMatrixElements() const;

    Matrix operator+(const Matrix& other) const;
    
    Matrix operator*(const Matrix& other) const;
    
    Matrix& operator=(const Matrix& other);

};

#endif
