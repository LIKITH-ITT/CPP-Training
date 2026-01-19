#include <iostream>
#include <string>

bool isAlphabet(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

float convertStringToFloat(const std::string &input) {
    float num = 0.0f, div = 1.0f;
    bool decimal = false, negative = false;
    bool hasNumberStarted = false;

        for (int i = 0; i < input.length(); i++) {

        // Alphabet validation
        if (isAlphabet(input[i])) {
            break;
        }
        // Space handling
        else if (input[i] == ' ') {
            if (hasNumberStarted) {
                break;
            }
            continue;
        }
        // Decimal point
        else if (input[i] == '.') {
            if (!decimal) {
                decimal = true;
            } else {
                break;
            }
        }
        // Plus sign
        else if (input[i] == '+') {
            if (hasNumberStarted) {
                break;
            }
        }
        // Minus sign
        else if (input[i] == '-') {
            if (!hasNumberStarted && !decimal) {
                negative = true;
            } else {
                break;
            }
        }
        // Digit handling
        else if (isDigit(input[i])) {
            hasNumberStarted = true;
            num = num * 10 + (input[i] - '0');
            if (decimal) {
                div *= 10;
            }
        }
        // Any other invalid character
        else {
            break;
        }
    }

    if (decimal) {
        num /= div;
    }

    if (negative) {
        num = -num;
    }

    return num;
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
