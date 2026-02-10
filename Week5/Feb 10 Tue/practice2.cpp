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

int main() {
    Derived d;
    d.show(10);  
    Base b = Derived();
    b.show(10);
}