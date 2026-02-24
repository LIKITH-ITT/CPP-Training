#include<iostream>
int main(){

struct Base { int x; };
struct Derived : Base { int y; };
Derived arr[3];
Base* p = arr; 
for (int i = 0; i < 3; i++) {
std::cout << p[i].x; 
}
}