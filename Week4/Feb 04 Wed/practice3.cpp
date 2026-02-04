#include <iostream>

int main()
{
    

    int arr[5] = {1,2,3,4,5};
    int (*p)[5] = &arr;

    std::cout << &arr[1] << std::endl;
    std::cout << p[1] << std::endl;   
    std::cout << (*p)[1] << std::endl;

    int* ptr[5];
    for(int i=0;i<5;i++)
    {
        ptr[i] = &arr[i];
    }
    std::cout << &arr[1] << std::endl;
    std::cout << ptr[1] << std::endl;   
    std::cout << *ptr[1] << std::endl;
}