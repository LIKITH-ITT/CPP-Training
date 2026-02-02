#include <iostream>

int main()
{
    int* oldArr = new int[3]{1, 2, 3};

    int* newArr = new int[5];

    for (int i = 0; i < 3; i++)
        newArr[i] = oldArr[i];

    newArr[3] = 4;
    newArr[4] = 5;

    delete[] oldArr; 

    oldArr = newArr; 

    for (int i = 0; i < 5; i++)
        std::cout << oldArr[i] << " ";

    delete[] oldArr;
}
