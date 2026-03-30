#include <iostream>
#include <string>

bool isAlphabet(char character) {
    return (character >= 'a' && character <= 'z') ||
           (character >= 'A' && character <= 'Z');
}

bool isDigit(char character) {
    return (character >= '0' && character <= '9');
}

bool isSpace(char character) {
    return character == ' ';
}

bool isDecimalPoint(char character) {
    return character == '.';
}

bool isPlusSign(char character) {
    return character == '+';
}

bool isMinusSign(char character) {
    return character == '-';
}

bool shouldStopParsingOnSpace(bool hasNumberStarted) {
    return hasNumberStarted;
}

bool isInvalidAlphabet(char character) {
    return isAlphabet(character);
}

bool isSecondDecimal(bool decimalUsed) {
    return decimalUsed;
}

float convertStringToFloat(const std::string &input) {
    float number = 0.0f;
    float divisor = 1.0f;

    bool decimalUsed = false;
    bool negative = false;
    bool hasNumberStarted = false;

    for (int index = 0; index < input.length(); index++) {
        char currentChar = input[index];

        if (isInvalidAlphabet(currentChar)) {
            break;
        }

        if (isSpace(currentChar)) {
            if (shouldStopParsingOnSpace(hasNumberStarted)) {
                break;
            }
            continue;
        }

        if (isDecimalPoint(currentChar)) {
            if (isSecondDecimal(decimalUsed)) {
                break;
            }
            decimalUsed = true;
            continue;
        }

        if (isPlusSign(currentChar)) {
            if (hasNumberStarted) {
                break;
            }
            continue;
        }

        if (isMinusSign(currentChar)) {
            if (!hasNumberStarted && !decimalUsed) {
                negative = true;
                continue;
            }
            break;
        }

        if (isDigit(currentChar)) {
            hasNumberStarted = true;
            number = number * 10 + (currentChar - '0');

            if (decimalUsed) {
                divisor *= 10;
            }
            continue;
        }

        break;
    }

    if (decimalUsed) {
        number /= divisor;
    }

    if (negative) {
        number = -number;
    }

    return number;
}


int main() {
    std::string input;
    int choice;
    bool loopRunning = true;

    while (loopRunning) {
        std::cout << "Enter your choice:\n";
        std::cout << "1. Enter a string\n";
        std::cout << "2. Exit program\n";

        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "Enter a string:\n";
                std::getline(std::cin, input);

                float result = convertStringToFloat(input);
                std::cout << result << std::endl;
                break;
            }
            case 2: {
                loopRunning = false;
            }
            default: {
                std::cout << "Enter a valid option...\n";
            }
        }
    }
    return 0;
}
