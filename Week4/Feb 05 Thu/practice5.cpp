#include <iostream>

int main()
{


    
    int* p = new int(10);
    std::cout << p<<std::endl;
    std::cout << *p<< std::endl;

    delete p;
    int* ptr = new int[5];
  

    std::cout << ptr+1<<std::endl;
    std::cout << *ptr+1<< std::endl;

    std::cout << p<<std::endl;
    std::cout << *p<< std::endl;
    *p = 20;
    std::cout << p<<std::endl;
    std::cout << *p<< std::endl;

}