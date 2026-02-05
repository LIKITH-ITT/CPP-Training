#include <iostream>

class Car {
private:
    int speed;
    int tyres = 4;

private:
    void setSpeed(int s) {
        speed = s;
    }
public:
    int accelerate();
    int getSpeed(int s) {
        setSpeed(s);
        return speed;
    }
};

int Car::accelerate(){
    speed+=10;
    return speed;
}

int main() {
    Car c1;
    Car c2;
    Car* p = &c1;
    // c1.setSpeed(100);
    // c2.setSpeed(60);
    std::cout << p->getSpeed(20) << std::endl;
    //std::cout << *p << std::endl;

    std::cout << c1.getSpeed(100) << std::endl;
    std::cout << c2.getSpeed(60) << std::endl;
    std::cout << c1.accelerate() << std::endl;
    //std::cout<< &c1.speed << std::endl;
    // std::cout<< &c1.tyres << std::endl;
    
}
