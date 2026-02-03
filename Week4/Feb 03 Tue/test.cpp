#include <iostream>
using namespace std;

int main()
{
    int a = 5;
    int* p = &a;
    int* q = p;

    int& r = a;
    int* ptr = &r;

    cout << "===== CASE 2 =====\n";

    cout << "a   = " << a << endl;
    cout << "p   = " << p << endl;
    cout << "q   = " << q << endl;

    // cout << "*a  = " << *a << endl;    

    cout << "*p  = " << *p << endl;
    cout << "*q  = " << *q << endl;

    cout << "&a  = " << &a << endl;
    cout << "&p  = " << &p << endl;
    cout << "&q  = " << &q << endl;

    cout << "ptr = " << ptr << endl;   
    //cout << "**q = " << **q << endl;   

    return 0;
}
