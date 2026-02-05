#include <iostream>

class Car {
private:
    int speed;
    int topSpeed;

public:
    Car(int s){
        speed = s;
    }

    int getSpeed() const{   // const member function
        return speed+10;
    }

    void setTopSpeed(int ts){
        topSpeed = ts;
    }

    // int getSpeed()  {   // const member function
    //     return speed+1;
    // }
    // int getSpeed() {        // non-const version
    //     return speed;
    // }

    void setSpeed(int s) {   // non-const member function
        speed = s;
    }
};

int main()
{
    const Car c(50);
    Car c1(50);

    std::cout << c.getSpeed() << std::endl;
    c1.setSpeed(100);
    std::cout << c1.getSpeed() << std::endl;
    c1.setSpeed(120);
    std::cout << c1.getSpeed() << std::endl;

    int i = 10;
    int* ip = &i;
    std::cout << *ip << std::endl;
    const int* a = &i;
    std::cout << *a << std::endl;
    *ip = 20;
    std::cout << *a << std::endl;
    //*a = 20;
    //int* b = a;
}
