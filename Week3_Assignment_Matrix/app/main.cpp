#include <iostream>
#include "menuHandler.h"
#include "matrixWorkflow.h"

int main()
{
    bool isProgramRunning = true;

    while (isProgramRunning)
    {
        displayMenu();
        int menuChoice = getMenuChoice();
        
        MatrixOperationFunction selectedOperation = selectOperation(menuChoice, isProgramRunning);
        
        if (!isProgramRunning)
        {
            continue;
        }
        
        performMatrixOperation(selectedOperation, menuChoice);
    }

    std::cout << "\nProgram exited successfully.\n";
    return 0;
}
