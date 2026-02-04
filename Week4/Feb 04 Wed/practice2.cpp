#include <iostream>



int main()
{
    const int i = 5;
    const int* ip = &i;

    char c = 'a';
    char* p = &c;

    const char a[5] = "dfrh";
    const char* b = a;

    char abc = 'a';
    char* ab = &abc;

    int arr[5] = {1,2,3,4,5};
    int *ar = arr; 
    
    std::cout << (void*)ab << std::endl;
    std::cout << *ab << std::endl;

    std::cout << (void*)p << std::endl;   
    std::cout << *p << std::endl;

    std::cout << (void*)b << std::endl;   
    std::cout << *b << std::endl;

    std::cout <<ar << std::endl;   
    std::cout << *ar << std::endl;
}