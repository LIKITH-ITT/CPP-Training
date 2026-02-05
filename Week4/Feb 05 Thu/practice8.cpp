#include <iostream>

class Base {
public:
    virtual void display() {
        std::cout << "Base" << std::endl;
    }
};

class Derived : public Base {
public:
    void display(){ 
        std::cout << "Derived" << std::endl;
    }
};




int main() {
    Base a;
    Derived b;
    Base* c = new Base;
    Base* d = new Derived;
    Derived* e = new Derived;

    a.display();
    b.display();
    c->display();
    d->display();
    e->display();

    
}
