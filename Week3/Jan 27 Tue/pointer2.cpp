#include <iostream>

int main()
{
    int value{ 5 };
    int* ptr{ new int{value} }; // allocate memory
    std::cout << ptr << std::endl;
    std::cout << *ptr << std::endl;


    delete ptr; // return memory back to operating system
    std::cout << ptr << std::endl;
    std::cout << *ptr << std::endl;

    ptr = &value; // reassign pointer to address of value
    std::cout << ptr << std::endl;
    std::cout << *ptr << std::endl;

}