#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger
{
public:
    static const std::string MENU_DISPLAY;

    static const std::string PROMPT_ROWS;
    static const std::string PROMPT_COLUMNS;
    static const std::string PROMPT_ELEMENT;
    static const std::string PROMPT_ENTER_MATRIX_A;
    static const std::string PROMPT_ENTER_MATRIX_B;
    static const std::string RESULT_MATRIX_LABEL;

    static const std::string ERROR_ADDITION_DIMENSION;
    static const std::string ERROR_MULTIPLICATION_DIMENSION;
    static const std::string ERROR_INVALID_INPUT;

    static const std::string EXIT_MESSAGE;

    static const int MIN_DIMENSION;
    static const int MAX_DIMENSION;
    static const int MIN_ELEMENT_VALUE;
    static const int MAX_ELEMENT_VALUE;
    static const int MIN_MENU_CHOICE;
    static const int MAX_MENU_CHOICE;

    static void printMenu();
    static void printExitMessage();
    static void printMatrixPrompt(const std::string& matrixName);
    static void printResultLabel();
    static void printAdditionError(int rows1, int cols1, int rows2, int cols2);
    static void printMultiplicationError(int cols1, int rows2);
};

#endif
