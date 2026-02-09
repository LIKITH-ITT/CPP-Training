#include "Matrix.h"

void Matrix::allocateMemory()
{
    matrixElements = new int*[rows]();
    
    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        matrixElements[rowIndex] = new int[columns]();
    }
}

void Matrix::deallocateMemory()
{
    if (matrixElements == nullptr)
        return;

    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        delete[] matrixElements[rowIndex];
    }
    
    delete[] matrixElements;
    matrixElements = nullptr;
}

Matrix::Matrix(int rows, int columns) : rows(rows), columns(columns), matrixElements(nullptr)
{
    allocateMemory();
}

Matrix::Matrix(const Matrix& other) : rows(other.rows), columns(other.columns), matrixElements(nullptr)
{
    allocateMemory();
    
    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < columns; columnIndex++)
        {
            matrixElements[rowIndex][columnIndex] = other.matrixElements[rowIndex][columnIndex];
        }
    }
}

Matrix::~Matrix()
{
    deallocateMemory();
}

int Matrix::getRows() const
{
    return rows;
}

int Matrix::getColumns() const
{
    return columns;
}

int** Matrix::getMatrixElements() const
{
    return matrixElements;
}

Matrix Matrix::operator+(const Matrix& other) const
{
    Matrix result(rows, columns);

    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < columns; columnIndex++)
        {
            result.matrixElements[rowIndex][columnIndex] = matrixElements[rowIndex][columnIndex] + other.matrixElements[rowIndex][columnIndex];
        }
    }

    return result;
}

Matrix Matrix::operator*(const Matrix& other) const
{
    Matrix result(rows, other.columns);

    for (int resultRowIndex = 0; resultRowIndex < rows; resultRowIndex++)
    {
        for (int resultColumnIndex = 0; resultColumnIndex < other.columns; resultColumnIndex++)
        {
            for (int commonIndex = 0; commonIndex < columns; commonIndex++)
            {
                result.matrixElements[resultRowIndex][resultColumnIndex] += matrixElements[resultRowIndex][commonIndex] * other.matrixElements[commonIndex][resultColumnIndex];
            }
        }
    }

    return result;
}

Matrix& Matrix::operator=(const Matrix& other)
{
    if (this == &other)
        return *this;

    deallocateMemory();
    
    rows = other.rows;
    columns = other.columns;
    
    allocateMemory();
    
    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < columns; columnIndex++)
        {
            matrixElements[rowIndex][columnIndex] = other.matrixElements[rowIndex][columnIndex];
        }
    }

    return *this;
}
