#include "Utility.h"
#include "Constants.h"
#include <iostream>


std::string Utility::readLine()
{
    std::string input;
    std::getline(std::cin, input);
    return input;
}

std::string Utility::getFilePath()
{
    std::string path;
    bool validPathEntered = false;

    while (!validPathEntered)
    {
        Logger::printMessage(Constants::MSG_ENTER_FILE_PATH);
        path = readLine();
        validPathEntered = Validator::isValidFilePath(path);
    }

    return path;
}

char Utility::getUserChoice()
{
    std::string input;
    bool validChoiceEntered = false;

    while (!validChoiceEntered)
    {
        Logger::printMessage(Constants::MSG_CONTINUE);
        input = readLine();
        validChoiceEntered = Validator::isValidChoice(input);
    }

    return input[0];
}
