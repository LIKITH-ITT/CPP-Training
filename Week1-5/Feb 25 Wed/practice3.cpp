#include <iostream>
using namespace std;

class Parent {
protected:
    int x;
public:
    Parent(int x) : x(x) {}
    void setX(int v) { x = v; }
    void print() const { cout << "x = " << x << "\n"; }
};

class Child : public Parent {
private:
    int y;
public:
    Child(int x, int y) : Parent(x), y(y) {}
    void setY(int v) { y = v; }
    void print() const {
        cout << "x = " << x << ", y = " << y << "\n";
    }
};

int main() {
    Child c(1, 2);
    Parent p = c;//slicing

    c.setX(10);
    c.setY(20);
    c.print();
    p.print();
}