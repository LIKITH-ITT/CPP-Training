#include<iostream>

class Car {
    
public:
int speed;
    static int totalCars;
    Car(){
        totalCars++;
    }
    void setSpeed(int speed) {
        speed = speed;
    }
};
int Car::totalCars = 0;
int main(){
    
    Car c1;
    Car c2;
    c1.setSpeed(100);

    Car::totalCars = 2;
    c1.totalCars=3;
    std::cout << c1.speed << std::endl;
    std::cout << c1.totalCars << std::endl;
    std::cout << c2.totalCars << std::endl;

}