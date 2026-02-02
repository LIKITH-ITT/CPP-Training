#include <iostream>

int main()
{
    for (int i = 0; i < 5; i++)
    {
        int* ptr = new int(i);
        std::cout << *ptr << '\n';

        // delete ptr; 
    }
}
