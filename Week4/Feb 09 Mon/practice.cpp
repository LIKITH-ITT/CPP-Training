#include<iostream>

class Animal {
public:
    void speak() {
        std::cout << "Animal sound\n";
    }
};

class Dog : public Animal {
public:
    void speak() {
        std::cout << "Dog barks\n";
    }
};

int main(){
    Animal* b = new Dog(); 
    Animal a = Dog();
    std::cout << sizeof(a) << std::endl;
    std::cout << sizeof(*b) << std::endl;
    a.speak();   // Dog barks

}