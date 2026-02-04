#include <iostream>
void foo()
{
    char * name;
    std::cout << name <<std::endl;
    std::cout << *(&name) << std::endl;
    std::cout << &name << std::endl;
}

int main()
{
    char* name = "Mee";
    std::cout << name <<std::endl;
    std::cout << *(&name) << std::endl;
    std::cout << &name << std::endl;
    std::cout << "\n";
    int i = 5;
    int* ip = &i;
    //std::cout << *i <<std::endl;
    std::cout << &i << std::endl;
    std::cout << ip <<std::endl;
    std::cout << &ip << std::endl;
    std::cout << *(&ip) << std::endl;

    foo();
    return 0;
}
