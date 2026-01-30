#include <iostream>

void getValidatedInput(int& value, int min, int max)
{
    while (true)
    {
        std::cin >> value;

        if (!std::cin.fail() && value >= min && value <= max)
            return;

        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input. Enter a value again between " << min << " and " << max << ": ";
    }
}

int** allocateMatrix(const int& rows, const int& columns)
{
    int** matrix = new int*[rows]();
    for (int row = 0; row < rows; row++)
    {
        matrix[row] = new int[columns]();
    }
    return matrix;
}

void freeMatrix(int**& matrix, const int& rows)
{
    if (matrix == nullptr)
        return;

    for (int row = 0; row < rows; row++)
    {
        delete[] matrix[row];
    }
    delete[] matrix;
    matrix = nullptr; 
}

void getMatrixInput(int** const& matrix, const int& rows, const int& columns)
{
    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            std::cout << "Enter element [" << row << "][" << column << "]: ";
            getValidatedInput(matrix[row][column], 1, 10);
        }
    }
}

void printMatrix(int** const& matrix, const int& rows, const int& columns)
{
    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            std::cout << matrix[row][column] << " ";
        }
        std::cout << '\n';
    }
}

int** addMatrices(int** const& matrixA, int** const& matrixB, const int& rows, const int& columns)
{
    int** resultMatrix = allocateMatrix(rows, columns);

    for (int row = 0; row < rows; row++)
        for (int column = 0; column < columns; column++)
        {
            resultMatrix[row][column] = matrixA[row][column] + matrixB[row][column];
        }

    return resultMatrix;
}

int** multiplyMatrices(int** const& matrixA, int** const& matrixB, const int& rows1, const int& columns1, const int& columns2)
{
    int** resultMatrix = allocateMatrix(rows1, columns2);

    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < columns2; j++)
        {
            for (int k = 0; k < columns1; k++)
            {
                resultMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    return resultMatrix;
}

int** performAddition(int** const& matrixA, int** const& matrixB, const int& rows1, const int& columns1, const int& rows2, const int& columns2)
{
    if (rows1 != rows2 || columns1 != columns2)
    {
        std::cout << "Addition not possible (dimension mismatch)\n";
        return nullptr;
    }

    return addMatrices(matrixA, matrixB, rows1, columns1);
}

int** performMultiplication(int** const& matrixA, int** const& matrixB, const int& rows1, const int& columns1, const int& rows2, const int& columns2)
{
    if (columns1 != rows2)
    {
        std::cout << "Multiplication not possible as column1 and row2 does not match\n";
        return nullptr;
    }

    return multiplyMatrices(matrixA, matrixB, rows1, columns1, columns2);
}

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
            std::cout << "Enter choice: ";

            int choice;
            std::cin >> choice;

            MatrixOperation selectedOperation = nullptr;

            switch (choice)
            {
                case 1:
                    selectedOperation = performAddition;
                    break;

                case 2:
                    selectedOperation = performMultiplication;
                    break;

                case 3:
                    performMoreOperations = false; // break inner loop
                    continue;

                case 4:
                    performMoreOperations = false;
                    isProgramRunning = false;
                    continue;

                default:
                    std::cout << "Invalid choice\n";
                    continue;
            }

            int** resultMatrix = selectedOperation(matrixA, matrixB, rows1, columns1, rows2, columns2);

            if (resultMatrix != nullptr)
            {
                std::cout << "\nResult Matrix:\n";

                if (choice == 1)
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
