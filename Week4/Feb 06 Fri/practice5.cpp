#include <iostream>
#include <vector>

class MyClass {
private:
    int b;

public:
    // MyClass(int a) : b(a){
    //     std::cout << "Parameterized" << std::endl;
    // }
    // Constructor
    MyClass(int &&a) : b(std::move(a)) {
        std::cout << "Move constructor called!" << std::endl;
    }

    void display() {
            std::cout << b <<std::endl;
    }
};

int main() {
    //int a = 4;

    MyClass obj1(std::move(5));  // Move constructor is called

    obj1.display();
    return 0;
}