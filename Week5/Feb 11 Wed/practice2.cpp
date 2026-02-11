#include<iostream>

class Base {
    // int val;
public:
    int val;
    Base(int val) : val(val){}
    static void show(int x) {
        std::cout << "Base\n";
    }
    int getVal()
    {
        return val;
    }
};

class Derived : public Base {
public:
    int speed;
    Derived(int x, int y) :Base(x), speed(y){}
    void show(int x) {
        std::cout << "Derived\n";
    }
};

int main() {
    Derived d(10,100);
    d.show(10);  
    std::cout << d.speed << std::endl;
    std::cout << d.val << std::endl;
    //Base::show(1);
    //  std::cout << d.getVal() << std::endl;
    // Base b = Derived();
    // b.show(10);
    Base* b = new Derived(20,200);
    b->show(1);
    //b->speed;
    b->val;
   
}