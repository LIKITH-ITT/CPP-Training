#include<iostream>

struct Animal {
virtual void speak() { std::cout << "...\n"; }
virtual ~Animal() {}
};
struct Dog : Animal {
void speak() override { std::cout << "Woof\n"; }
};
int main(){
Animal* a = new Dog();
a->speak();
delete a; 
Dog d;
Animal sliced = d; 
sliced.speak(); 
Animal& ref = d;
ref.speak(); 
Animal* dog = &d;
dog->speak();
}