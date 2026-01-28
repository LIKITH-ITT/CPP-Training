#include <iostream>

int main()
{
    int* p = new int(5);   
    delete p;
    
    std::cout << *p << std::endl; 
    std::cout << p << std::endl; 
}
