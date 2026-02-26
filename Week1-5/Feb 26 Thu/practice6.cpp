#include <iostream>

class Base {
public:
    virtual void show(int) {
        std::cout << "Base int\n";
    }
};

class Derived : public Base {
public:
    void show(double) {
        std::cout << "Derived double\n";
    }
};

int main() {
    Base* ptr = new Derived();
    ptr->show(10);
}