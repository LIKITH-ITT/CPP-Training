
#include <iostream>

int main(){

    int x = 10;
    int* p = &x;
    int** pp = &p;

    *pp = nullptr;

    std::cout << x << std::endl;
    std::cout << p << std::endl;
    //std::cout << *p << std::endl;
    std::cout << pp << std::endl;
}