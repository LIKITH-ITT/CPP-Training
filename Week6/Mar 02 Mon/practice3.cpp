#include <iostream>

int main()
{
    int *ptr = new int(5);

    delete ptr;      
    std::cout << *ptr << "\n";

    return 0;
}