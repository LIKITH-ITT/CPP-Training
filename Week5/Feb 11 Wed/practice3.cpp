// class Base {
//     int x = 0;
//     Base(int x = 0) : x(x){}
// };
 
// int main(){
//     Base b(2);
// }
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
};

int main()
{
    Base base {};
    base.identify();
    Derived derived {};
    derived.identify();

    return 0;
}