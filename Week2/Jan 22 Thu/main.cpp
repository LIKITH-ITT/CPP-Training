#include <iostream>
//extern int counter ;

void fun(){
    extern int counter;   // declaration
    std::cout << counter << std::endl;

}
int main() {
    extern int counter;
    fun();
    std::cout << counter << std::endl;
    counter += 5;
    std::cout << counter << std::endl;
}
