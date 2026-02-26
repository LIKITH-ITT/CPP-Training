#include <iostream>

class Base {
public:
    virtual void speak() { 
        std::cout << "Base\n"; 
    }
};

class Derived : public Base {
public:
    void speak() override { 
        std::cout << "Derived\n"; 
    }
};

void call(Base b) {
    b.speak();
}

int main() {
    Derived d;
    call(d);
}