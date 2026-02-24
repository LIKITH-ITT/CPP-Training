#include<iostream>
int main(){
    int a = 1, b = 2;
    int* p = &a;
    p = p + (&b - p);
    std::cout << *p;
}