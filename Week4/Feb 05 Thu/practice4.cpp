#include <iostream>
#include <cstring>

void foo()
{
    char * name;
    std::cout << name <<std::endl;
    std::cout << *(&name) << std::endl;
    std::cout << &name << std::endl;
}

int main()
{
    char* name = new char[3];
    strncpy(name, "Mee", 3);
    std::cout << *name <<std::endl;
    std::cout << name <<std::endl;

    int* ptr = new int();
    *ptr = 34;

    std::cout << ptr << std::endl;
    std::cout << *ptr << std::endl;
    std::cout << &ptr << std::endl;
    std::cout << *(&ptr) << std::endl;


    // std::cout << *(&name) << std::endl;
    // std::cout << &name << std::endl;
    // std::cout << "\n";
    // int i = 5;
    // int* ip = &i;
    // //std::cout << *i <<std::endl;
    // std::cout << &i << std::endl;
    // std::cout << ip <<std::endl;
    // std::cout << &ip << std::endl;
    // std::cout << *(&ip) << std::endl;

    // foo();
    return 0;
}
