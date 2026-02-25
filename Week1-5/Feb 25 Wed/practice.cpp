#include<iostream>
int main(){
    int a = 5, b = 6;
    int* ptr = &a;
    int* const* ptr1 = &ptr;
    //*ptr1 = &b;
    char ch = 'a';
    int c = 9;
    char* pc = &ch;
    std::cout << pc << std::endl;
}