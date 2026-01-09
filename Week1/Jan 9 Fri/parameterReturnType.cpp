#include <iostream>
using namespace std;

void function1(){
    cout << "No return type, no parameter\n";
}

void function2(int a, int b){
    cout << "No return type, Parameters " << a << " " << b << endl;
}

int function3(){
    cout << "Return type, no parameter\n";
    return 100;
}

int function4(int a, int b){
    cout << "Return type and parameters\n";
    return (a + b);
}

int main(){
    int a, b;
    cout << "Enter the values of parameters: ";
    cin >> a;
    cin >> b;
    
    function1();
    function2(a, b);
    cout << function3() << endl;
    cout << function4(a, b) << endl;
    return 0;

}