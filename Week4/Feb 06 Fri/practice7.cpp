#include<iostream>
class Car {
    public:
    int speed;
    int gear;

public:
    Car(){
        Car(0,1);
    }          
    Car(int s) : Car(s, 1) {}     
    Car(int s, int g)           
        : speed(s), gear(g) {}
};
 int main(){
    Car c1;       
    Car c2(80); 
    c2 = 100;   
    Car c3(100,5);
    std::cout << c1.speed << std::endl;
    std::cout << c2.speed << std::endl;

 }