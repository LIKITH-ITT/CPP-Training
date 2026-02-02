#include <iostream>
#include "menu_handler.h"
#include "matrix_workflow.h"

int main()
{
    bool isProgramRunning = true;

    while (isProgramRunning) 
    {
        int menuChoice = displayMenuAndGetChoice();
        bool shouldContinue = false;
        
        MatrixOperation selectedOperation = selectOperation(menuChoice, isProgramRunning);
        
        if (!isProgramRunning) {
            continue;
        }
        
        performMatrixOperation(selectedOperation, menuChoice);
    }

    std::cout << "\nProgram exited successfully.\n";
    return 0;
}
