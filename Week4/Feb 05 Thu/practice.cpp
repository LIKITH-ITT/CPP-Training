#include <iostream>

int main()
{
    int a = 10;
    const int* pt = &a;
    std::cout << pt<<std::endl;
    std::cout << *pt<< std::endl;
    std::cout << *(&a) <<std::endl;

    
    int* p = new int(10);
    std::cout << p<<std::endl;
    std::cout << *p<< std::endl;

    delete p;
    int* ptr = new int[5];
    delete ptr; 
    //ptr = nullptr;
    std::cout << ptr<<std::endl;
    std::cout << *ptr<< std::endl;

    std::cout << ptr+1<<std::endl;
    std::cout << *ptr+1<< std::endl;

    std::cout << p<<std::endl;
    std::cout << *p<< std::endl;
    *p = 20;
    std::cout << p<<std::endl;
    std::cout << *p<< std::endl;

}