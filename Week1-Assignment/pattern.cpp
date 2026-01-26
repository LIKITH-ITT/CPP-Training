#include <iostream>

void printLeftPattern(int elementCount) {
    for (int index = 0; index < elementCount; index++) {
        std::cout << (index % 2 == 0 ? 1 : 0) << " ";
    }
}

void printMiddlePattern(int totalRows) {
    for (int index = 0; index < totalRows; index++) {
        std::cout << (index % 2 == 0 ? 1 : 0) << " ";
    }
}

void printRightPattern(int elementCount) {
    for (int index = 0; index < elementCount; index++) {
        std::cout << (index % 2 == 0 ? 1 : 0);
        if (index != elementCount - 1) {
            std::cout << " ";
        }
    }
}

void printSpaces(int spaceCount) {
    for (int index = 0; index < spaceCount; index++) {
        std::cout << " ";
    }
}

void printPattern(int size) {
    int totalRows = 2 * size - 1;

    for (int rowIndex = 0; rowIndex < totalRows; rowIndex++) {
        int elementCount =
            (rowIndex < size) ? rowIndex + 1 : totalRows - rowIndex;

        if (rowIndex == totalRows / 2) {
            printMiddlePattern(totalRows);
        } else {
            printLeftPattern(elementCount);

            int spaceCount = (totalRows - 2 * elementCount) * 2;
            printSpaces(spaceCount);

            printRightPattern(elementCount);
        }

        std::cout << std::endl;
    }
}

int main() {
    int size;
    int choice;
    bool loopRunning = true;

    while (loopRunning) {
        std::cout << "1. Print pattern\n";
        std::cout << "2. Exit the program\n";
        std::cout << "Enter your choice:\n";

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                std::cout << "Enter the size of the pattern: ";
                std::cin >> size;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "Invalid input. Please enter a valid number.\n";
                    break;
                }

                printPattern(size);
                break;

            case 2:
                std::cout << "Exiting the program...";
                loopRunning = false;
                break;

            default:
                std::cout << "Enter the right option...\n";
        }
    }

    return 0;
}
