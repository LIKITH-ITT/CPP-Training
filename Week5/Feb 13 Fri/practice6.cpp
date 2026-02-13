#include<iostream>
class A {
private:
    int x = 5;
    friend class B;
    
};

class B {
public:
    void change(A& a) {
        a.x = 20;
    }
    void getA(A& a){
        std::cout << a.x;
    }
};

int main() {
    A obj;
    B b;
    b.change(obj);
    b.getA(obj);
}
