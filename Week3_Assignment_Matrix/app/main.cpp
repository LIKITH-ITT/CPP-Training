#include <iostream>

#include "validate_input.h"
#include "matrix_memory.h"
#include "matrix_io.h"
#include "matrix_operations.h"

int main()
{
    using MatrixOperation = int** (*)(int** const&, int** const&, const int&, const int&, const int&, const int&);

    bool isProgramRunning = true;

    while (isProgramRunning) 
    {
        int rows1, columns1, rows2, columns2;

        std::cout << "\nEnter rows of Matrix A: ";
        getValidatedInput(rows1, 1, 10);

        std::cout << "Enter columns of Matrix A: ";
        getValidatedInput(columns1, 1, 10);

        std::cout << "Enter rows of Matrix B: ";
        getValidatedInput(rows2, 1, 10);

        std::cout << "Enter columns of Matrix B: ";
        getValidatedInput(columns2, 1, 10);

        int** matrixA = allocateMatrix(rows1, columns1);
        int** matrixB = allocateMatrix(rows2, columns2);

        std::cout << "\nEnter Matrix A:\n";
        getMatrixInput(matrixA, rows1, columns1);

        std::cout << "\nEnter Matrix B:\n";
        getMatrixInput(matrixB, rows2, columns2);

        bool performMoreOperations = true;

        while (performMoreOperations)
        {
            std::cout << "\n----- Matrix Operations -----\n";
            std::cout << "1. Addition\n";
            std::cout << "2. Multiplication\n";
            std::cout << "3. Enter new matrices\n";
            std::cout << "4. Exit\n";
            std::cout << "Enter menuChoice: ";

            int menuChoice;
            std::cin >> menuChoice;

            MatrixOperation selectedOperation = nullptr;

            switch (menuChoice)
            {
                case 1:
                    selectedOperation = performAddition;
                    break;

                case 2:
                    selectedOperation = performMultiplication;
                    break;

                case 3:
                    performMoreOperations = false; 
                    continue;

                case 4:
                    performMoreOperations = false;
                    isProgramRunning = false;
                    continue;

                default:
                    std::cout << "Invalid menuChoice\n";
                    continue;
            }

            int** resultMatrix = selectedOperation(matrixA, matrixB, rows1, columns1, rows2, columns2);

            if (resultMatrix != nullptr)
            {
                std::cout << "\nResult Matrix:\n";

                if (menuChoice == 1)
                    printMatrix(resultMatrix, rows1, columns1);
                else
                    printMatrix(resultMatrix, rows1, columns2);

                freeMatrix(resultMatrix, rows1);
            }
        }

        freeMatrix(matrixA, rows1);
        freeMatrix(matrixB, rows2);
    }

    std::cout << "\nProgram exited successfully.\n";
    return 0;
}
