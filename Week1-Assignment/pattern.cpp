#include <iostream>

void printPattern(int size) {
    int totalRows = 2 * size - 1;

    for (int rowIndex = 0; rowIndex < totalRows; rowIndex++) 
    {

        int elementCount = (rowIndex < size)? rowIndex + 1 : totalRows - rowIndex;

        if (rowIndex == totalRows / 2) 
        {
            for (int columnIndex = 0; columnIndex < totalRows; columnIndex++) 
            {
                std::cout << (columnIndex % 2 == 0 ? 1 : 0) << " ";
            }
            std::cout << std::endl;
        } else 
        {
            for (int leftIndex = 0; leftIndex < elementCount; leftIndex++) 
            {
                std::cout << (leftIndex % 2 == 0 ? 1 : 0) << " ";
            }

            int spaceCount = (totalRows - 2 * elementCount) * 2;
            for (int spaceIndex = 0; spaceIndex < spaceCount; spaceIndex++) 
            {
                std::cout << " ";
            }

            for (int rightIndex = 0; rightIndex < elementCount; rightIndex++) 
            {
                std::cout << (rightIndex % 2 == 0 ? 1 : 0);
                if (rightIndex != elementCount - 1) 
                {
                    std::cout << " ";
                }
            }

            std::cout << std::endl;
        }
    }
}

int main() {
    int size, choice;

    while (true) 
    {
        std::cout << "1. Print pattern\n2. Exit the program\n(Choose an option)\n";
        std::cin >> choice;

        if (std::cin.fail()) 
        {
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) 
        {
            case 1: 
            {
                std::cout << "Enter the size of the pattern: ";
                std::cin >> size;

                if (std::cin.fail()) 
                {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "Invalid input. Please enter a valid number.\n";
                    break;
                }

                printPattern(size);
                break;
            }
            case 2: 
            {
                std::cout << "Exiting the program...";
                return 0;
            }
            default: 
            {
                std::cout << "Enter the right option...\n";
            }
        }
    }
}
