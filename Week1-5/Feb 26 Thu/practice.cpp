#include<iostream>
using namespace std;

class Animal {
    public:
    Animal(const string& n) : name(n) {
    cout << "Animal(" << n << ") constructed" << endl;
    }
string name;
};

class Flyable : virtual public Animal {
    public:
    Flyable() : Animal("") {} 
};

class Swimmable : virtual public Animal {
    public:
    Swimmable() : Animal("") {}
};

class FlyingFish : public Flyable, public Swimmable {
    public:
    FlyingFish() : Animal("FlyingFish"), Flyable(), Swimmable() {}//Base class constructor should be initialized
};

int main(){
    FlyingFish fish;
    cout << fish.name;
    return 0;
}