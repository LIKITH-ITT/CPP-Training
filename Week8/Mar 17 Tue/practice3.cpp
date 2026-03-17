#include<iostream>
template<typename T>
T func(int a, int b) {
    return (a + b);
}

int main() {
    //int x = func(10, 20);
    double y = func<double>(10, 20);

    //std::cout << x << std::endl;
    std::cout << y << std::endl;  
}