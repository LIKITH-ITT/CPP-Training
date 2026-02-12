#include <iostream>
using namespace std;

class Shape {
public:
    int val;
    void print(){
        std::cout << "A\n";
    }
    virtual void draw() = 0; //pure virtual function
};

class Circle : public Shape {
public:
    void draw() override {
        cout << "Drawing Circle\n";
    }
};

int main() {

    //Shape s;      
    
    Shape* s = new Circle(); 
    
    s->draw();    
    
    delete s;
}