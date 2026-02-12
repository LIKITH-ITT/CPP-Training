#include<iostream>
class A{
    public:
    void func(){
        std::cout << "A\n";
    }
};

class B : public A{
    public:
    // using A::func;
    void func(int x) {
        std::cout << x << std::endl;
    }
    // void func(){
        
    // }
};

int main(){
    B obj;
    //obj.func();//once it finds a function name with func the compiler doesnt go to the parent class to search func
    obj.func(10);
    
}