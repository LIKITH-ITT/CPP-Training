#include "Matrix.h"
#include "InputValidator.h"

void Matrix::allocateMemory()
{
    data = new int*[rows]();
    
    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        data[rowIndex] = new int[columns]();
    }
}

void Matrix::deallocateMemory()
{
    if (data == nullptr)
        return;

    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        delete[] data[rowIndex];
    }
    
    delete[] data;
    data = nullptr;
}

void Matrix::initializeToZero()
{
    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < columns; columnIndex++)
        {
            data[rowIndex][columnIndex] = 0;
        }
    }
}

Matrix::Matrix(int rows, int columns) : rows(rows), columns(columns), data(nullptr)
{
    allocateMemory();
    initializeToZero();
}

Matrix::Matrix(const Matrix& other) : rows(other.rows), columns(other.columns), data(nullptr)
{
    allocateMemory();
    
    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < columns; columnIndex++)
        {
            data[rowIndex][columnIndex] = other.data[rowIndex][columnIndex];
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

int** Matrix::getData() const
{
    return data;
}

void Matrix::inputFromConsole()
{
    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < columns; columnIndex++)
        {
            std::cout << "Enter element [" << rowIndex << "][" << columnIndex << "]: ";
            InputValidator::getValidatedInput(data[rowIndex][columnIndex], 1, 10);
        }
    }
}

void Matrix::displayToConsole() const
{
    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < columns; columnIndex++)
        {
            std::cout << data[rowIndex][columnIndex] << " ";
        }
        std::cout << '\n';
    }
}

Matrix Matrix::add(const Matrix& other) const
{
    Matrix result(rows, columns);

    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < columns; columnIndex++)
        {
            result.data[rowIndex][columnIndex] = data[rowIndex][columnIndex] + other.data[rowIndex][columnIndex];
        }
    }

    return result;
}

Matrix Matrix::multiply(const Matrix& other) const
{
    Matrix result(rows, other.columns);

    for (int resultRowIndex = 0; resultRowIndex < rows; resultRowIndex++)
    {
        for (int resultColumnIndex = 0; resultColumnIndex < other.columns; resultColumnIndex++)
        {
            for (int sumIndex = 0; sumIndex < columns; sumIndex++)
            {
                result.data[resultRowIndex][resultColumnIndex] += data[resultRowIndex][sumIndex] * other.data[sumIndex][resultColumnIndex];
            }
        }
    }

    return result;
}

bool Matrix::canAddWith(const Matrix& other) const
{
    return (rows == other.rows && columns == other.columns);
}

bool Matrix::canMultiplyWith(const Matrix& other) const
{
    return (columns == other.rows);
}
