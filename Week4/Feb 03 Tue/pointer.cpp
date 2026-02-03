#include <iostream>
using namespace std;

int main()
{
    int x = 10;

    int* p = &x;   
    int& r = x;    

    cout << "x  = " << x << endl;
    cout << "*p = " << *p << endl;
    cout << "r  = " << r << endl;

    *p = 20;
    cout << "After *p = 20, x = " << x << endl;

    r = 30;
    cout << "After r = 30, x = " << x << endl;
}
