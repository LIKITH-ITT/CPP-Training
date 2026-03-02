#include <iostream>

void func(int *ptr)
{
    *ptr = 10;   
}

int main()
{
    int *p = nullptr;
    std::cout << "Before crash\n";
    func(p);
    std::cout << "After crash\n";
    return 0;
}