#include <iostream>

class Base {
public:
    Base()  {
        std::cout << "Base ctor\n"; 
    }
    ~Base() { 
        std::cout << "Base dtor\n"; 
    }

    virtual void foo() { 
        std::cout << "Base foo\n"; 
    }
};

class Derived : public Base {
public:
    Derived()  { 
        std::cout << "Derived ctor\n"; 
    }
    ~Derived() { 
        std::cout << "Derived dtor\n"; 
    }

    void foo() override { 
        std::cout << "Derived foo\n"; 
    }
};

int main() {
    Base* ptr = new Derived();
    delete ptr;
}