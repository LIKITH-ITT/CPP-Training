#include<iostream>
class Base {
public:
    virtual void display() {
        std::cout << "Base\n";
    }
};

class Derived : public Base {
public:
    int val = 0;
    void display() {  //override gives a compilation error as the signature dosent match
        std::cout << "Derived\n";
    }
};
int main()
{
    Derived d;
    Base* ptr1 = new Derived();
    Base* ptr2 = &d;
    ptr1->display();
    ptr2->display();
    // std::cout << ptr1->val << std::endl;
    // std::cout << ptr2->val << std::endl;

}