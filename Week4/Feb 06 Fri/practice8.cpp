#include <iostream>

class Grandparent {
public:
    Grandparent() {
        std::cout << "Grandparent constructor called" << std::endl;
    }
};

class Parent : public Grandparent {
public:
    Parent() {
        std::cout << "Parent constructor called" << std::endl;
    }
};

class Child : public Parent {
public:
    Child() {
        std::cout << "Child constructor called" << std::endl;
    }
};

int main() {
    Child c;
    std::cout << std::endl;
    Grandparent gp =  Parent();
    return 0;
}
