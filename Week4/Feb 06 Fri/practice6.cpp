#include<iostream>
class Car {
    int speed;
    int gear;

public:
    Car() {                
        speed = 0;
        gear = 1;
    }

    Car(int s) {      
        speed = s;
        gear = 1;
    }

    Car(int s, int g) {    
        speed = s;
        gear = g;
    }
};

int main(){
Car c1;         
Car c2(80);      
Car c3(100, 5);  
}
