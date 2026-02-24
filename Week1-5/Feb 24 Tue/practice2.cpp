#include<iostream>

int main(){
// int arr[5] = {1, 2, 3, 4, 5};
// int* p = arr; 
// int (*pa)[5] = &arr; 
// std::cout << (pa) << std::endl;
// std::cout << &arr << std::endl;
// p++; 
// pa++; 
int a = 1, b = 2, c = 3;
// int* ptrs[3] = {&a, &b, &c};
// std::cout << *ptrs[1]; 

int&& rref = 42;
int* p = &rref;
std::cout << &rref << std::endl;
std::cout << *p << std::endl;
std::cout << p << std::endl;
int& ref = a;
std::cout << &ref << std::endl;
std::cout << &a << std::endl;

// int arr[5] = {10, 20, 30, 40, 50};
// int* end = arr + 3; 
// std::cout << *end;

// int arr[5] = {1, 2, 3, 4, 5};
// int sum = 0;
// for (int* p = arr; p != arr + 5; ++p) {
// sum += *p;
// }
// std::cout << sum << std::endl;

}

