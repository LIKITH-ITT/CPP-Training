#ifndef MATRIX_DIMENSION_H
#define MATRIX_DIMENSION_H

class MatrixDimension
{
private:
    int rows;
    int columns;

public:
    MatrixDimension();
    MatrixDimension(int rows, int columns);

    int getRows() const;
    int getColumns() const;

    void setRows(int rows);
    void setColumns(int columns);

    void inputFromConsole(const char* matrixName);

    bool isValidForAddition(const MatrixDimension& other) const;
    bool isValidForMultiplication(const MatrixDimension& other) const;

    void displayAdditionMismatchError(const MatrixDimension& other) const;
    void displayMultiplicationMismatchError(const MatrixDimension& other) const;
};

#endif
