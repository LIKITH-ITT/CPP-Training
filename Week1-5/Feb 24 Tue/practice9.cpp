#include<iostream>
int main(){
int arr[] = {10, 20, 30, 40, 50};
int* p = arr + 1;
std::cout << *++p << ' ' << *(p-1) << ' ' << p[-2] << std::endl;

int a[3][4];
int (*pt)[4] = a;
std::cout << sizeof(a) << ' ' << sizeof(*pt) << ' ' << sizeof(pt);

//int* const* c = p; 
int ar[3] = {1, 2, 3};
int* ptr = ar;
std::cout << ptr++ << ' ' << *ptr << ' ' << ar;

}