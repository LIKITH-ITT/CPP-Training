#include<iostream>
class Base {
public:
    int val;
    Base(int x):val(x){}
    void display() {
        std::cout << "Base\n";
    }
};

class Derived : public Base {
public:
    int val;
    Derived(int x, int y):Base(x),val(y){}
    void display() {  //override gives a compilation error as the signature dosent match
        std::cout << "Derived\n";
    }
};

class Child : public Derived {
public:
int val;
    Child(int x, int y,int z):Derived(x,y),val(z){}
};

int main(){
    Child c(1,2,3); 
    Derived* d = &c;
    std::cout << d->val;//Even though c points to the entire child object the compiler keeps 
                        //a track of the offset at which derived subobject is present and copies only from the derived subobject
}