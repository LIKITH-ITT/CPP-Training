#include <iostream>

void D()
{
    std::cout << "Start D\n";
    throw 42;
    std::cout << "End D\n";
}

void C()
{
    std::cout << "Start C\n";
    D();
    std::cout << "End C\n";
}

void B()
{
    std::cout << "Start B\n";
    try
    {
        C();
    }
    catch (int e)
    {
        std::cout << "Caught in B: " << e << "\n";
    }
    std::cout << "End B\n";
}

int main()
{
    B();
}