#include <iostream>
#include <string_view>

class A
{
public:
    virtual std::string_view getName(){ return "A"; }
};

class B: public A
{
public:
    std::string_view getName(){ return "B"; }
};

class C: public B
{
public:
};

class D: public C
{
public:
    std::string_view getName() { return "D"; }
};

int main()
{
    C c ;
    D d;
    A& rBase{ d };
    B& bref(d);
    B* bptr = new D();
    std::cout << rBase.getName() << '\n';
    std::cout << bref.getName() << '\n';
    std::cout << bptr->getName() << '\n';

    return 0;
}