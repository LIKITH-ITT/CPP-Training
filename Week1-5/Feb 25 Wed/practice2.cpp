#include <iostream>
using namespace std;

class Base {
protected:
    int value;
public:
    Base(int v) : value(v) {}
    void show() const {
        cout << "Base value: " << value << "\n";
    }
};

class Derived : public Base {
private:
    int extra;
public:
    Derived(int v, int e) : Base(v), extra(e) {}
    void show() const {
        cout << "Derived value: " << value << ", extra: " << extra << "\n";
    }
};

void print(Base b) {  
    b.show();
}

int main() {
    Derived d(10, 99);
    d.show();
    Base b = d;      
    b.show();
    print(d);        
}