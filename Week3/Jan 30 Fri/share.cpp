#include <iostream>
#include <memory>
using namespace std;

class Rectangle {
    int length, breadth;

public:
    Rectangle(int l, int b) : length(l), breadth(b) {}
    int area() { return length * breadth; }
};

int main() {
    shared_ptr<Rectangle> P1(new Rectangle(10, 5));
    shared_ptr<Rectangle> P2(P1);

    cout << P1->area() << endl;
    cout << P2.use_count() << endl;
    cout << P1.use_count() << endl;
    return 0;
}