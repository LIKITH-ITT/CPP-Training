#include <iostream>
//#include <exception>

// Custom exception class
class NegativeValueException : public std::exception {
    
public:
    // Constructor
    int value;
    NegativeValueException(int val){
        value = val;
    }
    // Override what() method
    const char* what() const noexcept{
        return "Negative value error occurred!";
    }

    // Optional: method to get the invalid value
    int getValue() const {
        return value;
    }
};

// Function that throws the custom exception
void checkValue(int x) {
    if (x < 0) {
        throw NegativeValueException(x);
    }
    else {
        std::cout << "Value is: " << x << std::endl;
    }
}

int main() {
    int numbers[] = {10, -5, 20};

    for (int n : numbers) {
        try {
            checkValue(n);
        }
        catch (NegativeValueException &e) {
            std::cout << "Exception caught: " << e.what() 
                 << " Value = " << e.getValue() << std::endl;
        }
    }

    return 0;
}