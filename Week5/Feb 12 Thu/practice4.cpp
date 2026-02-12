#include<iostream>
class A
{
public:
    int _A;
    A(int x):_A(x){}
    virtual void print(){
        std::cout << "A\n";
    }
};

class B:public A
{
public:
    int _B;
    B(int x, int y):A(x),_B(y){}
    void print(){
        std::cout << "B\n";
    }
};

class C: public B
{
public:
    int _C;
    C(int x, int y,int z):B(x,y),_C(z){}
    void print(){
        std::cout << "C\n";
    }
};

int main(){
    A a(1);
    B b(10,20);
    C c(100,200,300);

    A* aa;
    aa = &c;
    //a = &b;
    aa->print();
}