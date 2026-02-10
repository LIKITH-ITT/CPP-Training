#include<iostream>

class Base {
public:
    void show(int x) {
        std::cout << "Base int\n";
    }
};

class Derived : public Base {
public:
    void show(double x) {
        std::cout << "Derived double\n";
    }
};

constexpr int square(int x) {
    return x * x;
}


int main() {
    // int c = 0;
    // std::cin >> c;
    constexpr int a = square(5);  // compile-time
    int b = square(10);           // runtime (also OK)


}