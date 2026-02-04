#include <iostream>
#pragma pack(push,1)
class Car {
private:
    char d;
    char a;
    int b;
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
#pragma pack(pop)
int main() {
    Car c1;
    Car c2;
    std::cout << sizeof(c1) << std::endl;
    // c1.setSpeed(100);
    // c2.setSpeed(60);

    std::cout << c1.getSpeed(100); 
    std::cout << c2.getSpeed(60); 
}
