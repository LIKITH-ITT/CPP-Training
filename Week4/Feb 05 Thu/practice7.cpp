#include <iostream>

class Car {
private:
    int speed = 0;
    int tyres = 4;

public:
    void setSpeed(int s) {
        if (s >= 0)      
            speed = s;
    }

    int getSpeed() {
        return speed;
    }

    int accelerate() {
        speed += 10;
        return speed;
    }

};

int main() {
    Car c1;
    Car c2;

    c1.setSpeed(-1);
    c2.setSpeed(60);

    std::cout << c1.getSpeed() << std::endl;
    std::cout << c2.getSpeed() << std::endl;
    std::cout << c1.accelerate() << std::endl;
    //std::cout<< &c1.speed << std::endl;
    // std::cout<< &c1.tyres << std::endl;
    //Car* p = &c1;
    //p->speed=100;
    int* p = (int*)&c1;
    *p = 42;
    std::cout << c1.getSpeed() << std::endl;

    
}
