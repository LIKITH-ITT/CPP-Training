#include <iostream>

int main()
{
    int* a = nullptr;
    int* z = NULL;
    std::cout << a << std::endl;
    std::cout << z << std::endl;

    int x = 5, b = 11;
    int& ref = x;

    std::cout << x << ref << '\n';

    x = 6;
    std::cout << x << ref << '\n';
    ref = b;
    std::cout << x << ref << b << '\n';
    ref = 7;
    std::cout << x << ref << b << '\n';


    return 0;
}
