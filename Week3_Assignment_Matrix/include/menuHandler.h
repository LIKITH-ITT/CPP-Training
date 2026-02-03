#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include "matrixTypes.h"

int getMenuChoice();

void displayMenu();

MatrixOperationFunction selectOperation(int menuChoice, bool& shouldContinue);

#endif
