#include <iostream>

void counter() {
    static int x = 0;    x++;
    std::cout << x << std::endl;
}

int main() {
    counter();  
    counter();  
    counter();  
}
