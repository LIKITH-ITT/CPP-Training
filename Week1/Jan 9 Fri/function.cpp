#include <iostream>
using namespace std;

int add(int a, int b){
    return (a + b);
}

int subtract(int a, int b){
    return (a - b);
}

int multiply(int a, int b){
    return (a * b);
}

int divide(int a, int b){
    return (a / b);
}

int modulo(int a, int b){
    return (a % b);
}

int main(){
    int a, b;

    cout << "Enter a and b: ";
    cin >> a;
    cin >> b;
    
    cout << "Addition of " << a << " and " << b << " is: " << add(a, b) << endl;
    cout << "Subtraction of " << a << " and " << b << " is: " << subtract(a, b) << endl;
    cout << "Multiplication of " << a << " and " << b << " is: " << multiply(a, b) << endl;
    cout << "Division of " << a << " and " << b << " is: " << divide(a, b) << endl;
    cout << "Modulus of " << a << " and " << b << " is: " << modulo(a, b) << endl;

    return 0;
}