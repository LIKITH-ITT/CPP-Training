#include<iostream>
#define CASE 6
int main(){
    int option = 1;
    const int x =10;
    int i =2;
    switch(option)
    {
        case x:std::cout << "first\n";break;
        case 2*4:std::cout << "second\n";break;
        default: std::cout << "default\n";break;
        case CASE:std::cout << "third\n";break;
            std::cout << "Valid";
            break;
    }
}