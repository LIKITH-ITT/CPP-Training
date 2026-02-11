#include <iostream>

class Base
{
public:
    Base() { }

    void identify() { 
        std::cout << "Base::identify()\n";
        
     }
};

class Derived: public Base
{
public:
    Derived() { }

    void identify() 
    {
        std::cout << "Derived::identify()\n";
        Base::identify(); 
    }
    void print(double x){
        std::cout << "Double\n";
    }
    void print(long x){
        std::cout << "Long\n";
    }
    
};

int main()
{
    
    Derived d;
    d.print(static_cast<long>(1.0));
    //d.print(1);

    return 0;
}