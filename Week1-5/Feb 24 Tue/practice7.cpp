#include<iostream>

int main(){
    int arr[5] = {1, 2, 3, 4, 5};
    int* p = arr; 
    int (*pa)[5] = &arr; 
    std::cout << (pa) << std::endl;
    std::cout << &arr << std::endl;
    p++; 
    pa++; 

    int a = 1, b = 2, c = 3;
    int* ptrs[3] = {&a, &b, &c};
    std::cout << *ptrs[1]; 

}

