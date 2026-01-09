#include<iostream>
using namespace std;

void factorial(){

    short int n;
    int factorial = 1;
    cout << "Enter a number: \n";
    cin >> n;

    for (int i = 1; i <= n; i++){
        factorial = factorial * i;
    }

    cout << "Factorial of " << n << " is: "<< factorial << endl;
}

void fibonacci(){
    short int n;
    short int first = 1, second = 1;
    
    cout << "Enter a number for fibonacci series:\n";
    cin >> n;

    cout << first << " ";
    cout << second << " ";
    int fib = 0;
    for (int i = 2; i < n; i++){
        fib = first + second;
        first = second;
        second = fib;
        cout << fib << " ";
    }

}

int main(){
    factorial();
    fibonacci();
}