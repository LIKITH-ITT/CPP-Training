#include <iostream>

void increment(int& x)   // x is a reference
{
    x++;                // modifies caller's variable
}

void decrement(int x){ //no reference
    x--;
}

int main()
{
    int x = 10;
    std::cout << x << std::endl;
    increment(x);
    std::cout << x << std::endl;
    decrement(x);
    std::cout << x << std::endl;
}
