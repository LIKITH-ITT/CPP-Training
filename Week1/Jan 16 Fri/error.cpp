#include <cassert>
#include <iostream>

void check_value(int value) {
    // Assert that the value is within an expected range
    assert(value >= 0 && value <= 100 && "Value out of expected range");
    std::cout << "Value is valid: " << value << std::endl;
}

int main() {
    check_value(230);
    // This call will terminate the program with an assertion failure message during development
    // check_value(150); 
    return 0;
}
