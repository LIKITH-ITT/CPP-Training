#include <cstddef>
#include <iostream>

int main()
{
    
    int x = 10;
    void* p = &x;
    std::cout << p << std::endl;
    std::cout << sizeof(p) << std::endl;
    std::cout << static_cast<int*>(p) << std::endl;
    int* ptr = static_cast<int*>(p);
    std::cout << *ptr << std::endl;
    
    return 0;
}