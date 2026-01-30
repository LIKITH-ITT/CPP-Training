#include <iostream>

void increment(int& x)  
    x++;               
}

int main()
{

int* p;
{
    int x = 10;
    p = new int(x);
} 

std::cout << *p;  // still valid
delete p;
}
