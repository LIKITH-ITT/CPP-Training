#include<iostream>
using namespace std;
int main(){
    int a =5;
    int* ptr=&a;
    cout << ptr << endl;
    cout << *ptr << endl;
    cout << &a << endl;
    int& ref = *ptr;
    ref = 4;
    cout << a << endl;
    // int* ptr1 = nullptr ;
    // int& ref1 = *ptr1;
    // cout << ptr1 << endl;

    //cout << ref1 << endl;
    cout << *(ptr+1) << endl;


}