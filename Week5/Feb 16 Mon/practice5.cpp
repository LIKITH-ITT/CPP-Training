#include <iostream>

class Base {
public:
    int baseValue;

    Base(int b) : baseValue(b) {}

    virtual void show() {
        std::cout << "Base show(), baseValue = " << baseValue << "\n";
    }
};

class Derived : public Base {
public:
    int derivedValue;

    Derived(int b, int d) : Base(b), derivedValue(d) {}

    void show() override {
        std::cout << "Derived show(), baseValue = "
             << baseValue << ", derivedValue = "
             << derivedValue << "\n";
    }
};

int main() {
    Derived d(10, 20);

    Base b = d;  
    b.show();  //d is sliced 

    Base* b1 = &d;
    b1->show();

    return 0;
}