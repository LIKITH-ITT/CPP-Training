#include <iostream>

class Box {
private:
    int value;

public:
    Box(int v) : value(v) {}

    friend void printValue(const Box& b);
};

void printValue(const Box& b) {
    std::cout << b.value ;  //accessing private
}

int main() {
    Box b(10);
    printValue(b);
}