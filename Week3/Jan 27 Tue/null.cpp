#include <cstddef>
#include <iostream>

int main()
{
    int* ptr{nullptr};
    std::cout << ptr << std::endl;
    std::cout << sizeof(ptr) << std::endl;
    std::cout << *ptr << std::endl;
    
    return 0;
}