#include<iostream>
using namespace std;
class A {
public:
    int* data;

    A(int val) {
        data = new int(val);
    }

    ~A() {
        delete data;
    }
};
int main()
{
    A a1(10);
    cout << "a1's x = " << *a1.data << endl;

    A a2(a1);
    cout << "a2's x = " << *a2.data << endl;
    *a1.data = 20;
    cout << "a1's x = " << *a1.data << endl;
    cout << "a2's x = " << *a2.data << endl;

    return 0;
}