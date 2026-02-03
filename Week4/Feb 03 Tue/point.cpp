#include <iostream>


 
int main() {
    int a[10];
    int b =5;
    int* ptr = &b;
    char abc = 'a';
    char* ab = &abc;
    
    std::cout << *ab << std::endl;
    std::cout << ptr+1 << std::endl;
    std::cout << 1+ptr << std::endl;
    std::cout << &a+1 << std::endl;
    
}