#include <iostream>

class Base
{
protected:
    int value;

public:
    Base(int value): value{ value }{}

    std::string getName(){ 
        return "Base"; 
    }
    int getValue(){ 
        return value; 
    }
};
class Derived: public Base
{
    int x = 10;
public:
    Derived(int value): Base{ value }{}

    std::string getName()
    { 
        return "Derived"; 
    }
    int getValue()
    { 
        return value * 2; 
    }
};
#include <iostream>

int main()
{
    Derived derived{ 5 };
    std::cout << "derived is a " << derived.getName() << " and has value " << derived.getValue() << '\n';
    std::cout << &derived << std::endl;

    Derived& rDerived{ derived };
    std::cout << "rDerived is a " << rDerived.getName() << " and has value " << rDerived.getValue() << '\n';
    std::cout << &rDerived << std::endl;

    Derived* pDerived{ &derived };
    std::cout << "pDerived is a " << pDerived->getName() << " and has value " << pDerived->getValue() << '\n';
    std::cout << &pDerived << std::endl;
    std::cout << pDerived << std::endl;

    Base& rBase{ derived }; 
    Base* pBase{ &derived };
    std::cout << "rBase is a " << rBase.getName() << " and has value " << rBase.getValue() << '\n';
    std::cout << "pBase is a " << pBase->getName() << " and has value " << pBase->getValue() << '\n';

    return 0;
}