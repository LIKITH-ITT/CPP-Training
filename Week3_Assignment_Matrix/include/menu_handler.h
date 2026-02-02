#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include "matrix_operations.h"

using MatrixOperation = int** (*)(int** const&, int** const&, const int&, const int&, const int&, const int&);

int displayMenuAndGetChoice();

MatrixOperation selectOperation(const int menuChoice, bool& shouldContinue);

#endif
