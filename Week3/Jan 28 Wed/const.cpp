#include <iostream>

int main()
{
    int a = 10;
    int b = 20;

    const int *p;
    p=&a;

    std::cout << *p << std::endl;

    // Try uncommenting one line at a time
    // *p = 15;      
    p = &b;         

    std::cout << *p << std::endl;
}
