#include <iostream>

class A
{
public:
    virtual void fun()
    {
        std::cout << "public A::fun()\n";
    }
};

class B : public A
{
private:
    virtual void fun()
    {
         std::cout << "private B::fun()\n";
   }
};

int main()
{
    B b {};
    //b.fun();                  
    static_cast<A>(b).fun();

    return 0;
}
