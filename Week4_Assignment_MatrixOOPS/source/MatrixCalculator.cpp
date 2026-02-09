#include "MatrixCalculator.h"
#include "Logger.h"
#include "Validator.h"
#include <iostream>

MatrixCalculator::MatrixCalculator() : isProgramRunning(true)
{
}

void MatrixCalculator::displayMenu() const
{
    Logger::printMenu();
}

MenuOption MatrixCalculator::getMenuChoice()
{
    int choice;
    Validator::getValidatedInput(choice, Logger::MIN_MENU_CHOICE, Logger::MAX_MENU_CHOICE);
    return static_cast<MenuOption>(choice);
}

void MatrixCalculator::getDimensionsFromConsole(int& rows, int& columns, const char* matrixName)
{
    std::cout << "\n" << Logger::PROMPT_ROWS << matrixName << ": ";
    Validator::getValidatedInput(rows, Logger::MIN_DIMENSION, Logger::MAX_DIMENSION);

    std::cout << Logger::PROMPT_COLUMNS << matrixName << ": ";
    Validator::getValidatedInput(columns, Logger::MIN_DIMENSION, Logger::MAX_DIMENSION);
}

void MatrixCalculator::readMatrixFromConsole(Matrix& matrix)
{
    int** matrixElements = matrix.getMatrixElements();
    int rows = matrix.getRows();
    int columns = matrix.getColumns();

    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < columns; columnIndex++)
        {
            std::cout << Logger::PROMPT_ELEMENT << "[" << rowIndex << "][" << columnIndex << "]: ";
            Validator::getValidatedInput(matrixElements[rowIndex][columnIndex], Logger::MIN_ELEMENT_VALUE, Logger::MAX_ELEMENT_VALUE);
        }
    }
}

void MatrixCalculator::printMatrix(const Matrix& matrix) const
{
    int** matrixElements = matrix.getMatrixElements();
    int rows = matrix.getRows();
    int columns = matrix.getColumns();

    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < columns; columnIndex++)
        {
            std::cout << matrixElements[rowIndex][columnIndex] << " ";
        }
        std::cout << '\n';
    }
}

void MatrixCalculator::addMatrix()
{
    int rowsA, columnsA, rowsB, columnsB;
    
    getDimensionsFromConsole(rowsA, columnsA, "A");
    getDimensionsFromConsole(rowsB, columnsB, "B");

    // Check if dimensions are valid for addition
    if (rowsA != rowsB || columnsA != columnsB)
    {
        Logger::printAdditionError(rowsA, columnsA, rowsB, columnsB);
        return;
    }

    Matrix matrixA(rowsA, columnsA);
    Matrix matrixB(rowsB, columnsB);

    Logger::printMatrixPrompt("A");
    readMatrixFromConsole(matrixA);

    Logger::printMatrixPrompt("B");
    readMatrixFromConsole(matrixB);

    Matrix resultMatrix = matrixA + matrixB;

    Logger::printResultLabel();
    printMatrix(resultMatrix);
}

void MatrixCalculator::multiplyMatrix()
{
    int rowsA, columnsA, rowsB, columnsB;
    
    getDimensionsFromConsole(rowsA, columnsA, "A");
    getDimensionsFromConsole(rowsB, columnsB, "B");

    if (columnsA != rowsB)
    {
        Logger::printMultiplicationError(columnsA, rowsB);
        return;
    }

    Matrix matrixA(rowsA, columnsA);
    Matrix matrixB(rowsB, columnsB);

    Logger::printMatrixPrompt("A");
    readMatrixFromConsole(matrixA);

    Logger::printMatrixPrompt("B");
    readMatrixFromConsole(matrixB);

    Matrix resultMatrix = matrixA * matrixB;

    Logger::printResultLabel();
    printMatrix(resultMatrix);
}

void MatrixCalculator::run()
{
    while (isProgramRunning)
    {
        displayMenu();
        MenuOption choice = getMenuChoice();
        
        switch (choice)
        {
            case MenuOption::ADDITION:
                addMatrix();
                break;

            case MenuOption::MULTIPLICATION:
                multiplyMatrix();
                break;

            case MenuOption::EXIT:
                isProgramRunning = false;
                break;
        }
    }

    Logger::printExitMessage();
}
