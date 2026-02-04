#include <iostream>

int main()
{
    char* name = "Mee";
    std::cout << (void*)name <<std::endl;
    std::cout << (void*)&name << std::endl;

    return 0;
}
