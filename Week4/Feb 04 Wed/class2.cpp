#include <iostream>

class Car {
private:
    int speed;

private:
    void setSpeed(int s) {
        speed = s;
    }
public:
    int getSpeed(int s) {
        setSpeed(s);
        return speed;
    }
};

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
}
