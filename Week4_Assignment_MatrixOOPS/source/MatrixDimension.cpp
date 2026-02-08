#include <iostream>
#include "MatrixDimension.h"
#include "InputValidator.h"

MatrixDimension::MatrixDimension() : rows(0), columns(0)
{
}

MatrixDimension::MatrixDimension(int rows, int columns) : rows(rows), columns(columns)
{
}

int MatrixDimension::getRows() const
{
    return rows;
}

int MatrixDimension::getColumns() const
{
    return columns;
}

void MatrixDimension::setRows(int rows)
{
    this->rows = rows;
}

void MatrixDimension::setColumns(int columns)
{
    this->columns = columns;
}

void MatrixDimension::inputFromConsole(const char* matrixName)
{
    std::cout << "\nEnter rows of Matrix " << matrixName << ": ";
    InputValidator::getValidatedInput(rows, 1, 10);

    std::cout << "Enter columns of Matrix " << matrixName << ": ";
    InputValidator::getValidatedInput(columns, 1, 10);
}

bool MatrixDimension::isValidForAddition(const MatrixDimension& other) const
{
    return (rows == other.rows && columns == other.columns);
}

bool MatrixDimension::isValidForMultiplication(const MatrixDimension& other) const
{
    return (columns == other.rows);
}

void MatrixDimension::displayAdditionMismatchError(const MatrixDimension& other) const
{
    std::cout << "*****************************************************";
    std::cout << "\nAddition requires matrices with identical dimensions.\n";
    std::cout << "Matrix A is " << rows << "x" << columns 
              << " but Matrix B is " << other.rows << "x" << other.columns << "\n";
    std::cout << "Please try again with matching dimensions.\n";
    std::cout << "*****************************************************\n";
}

void MatrixDimension::displayMultiplicationMismatchError(const MatrixDimension& other) const
{
    std::cout << "********************************************************************";
    std::cout << "\nFor multiplication, columns of Matrix A must equal rows of Matrix B.\n";
    std::cout << "Matrix A has " << columns << " columns but Matrix B has " 
              << other.rows << " rows.\n";
    std::cout << "Please try again with compatible dimensions.\n";
    std::cout << "********************************************************************\n";
}
