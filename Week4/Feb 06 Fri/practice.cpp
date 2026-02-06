#include<iostream>

class Foo
{
    int m_x;
    int m_y;
public:
    Foo(int x, int y){
        m_x = x;
        m_y = y;
    }
    Foo(int x){
        m_x = x;
    }
};

int main()
{
    Foo foo { 6 }; 

    return 0;
}