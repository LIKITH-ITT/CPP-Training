#include<iostream>

class Foo
{
    public:
    int m = -99;
    int n = -99;
public:
    //Foo(){}
    Foo(int m, int y){
        if(m>0)
        m = m;
        n = y;
    }
    void setter(int x, int y){
        m = x;
        n = y;
    }
    void getter(){
        std::cout << m << " " << n << std::endl;
    }
};

int main()
{
    Foo obj(5,10); 
    obj = {100,20};
    obj.getter();
    obj.setter(10,10);
    obj.getter();

    return 0;
}