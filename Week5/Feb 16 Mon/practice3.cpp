#include<iostream>
using namespace std;

class A{
    public:
    int* data;
    const int v;
    
    A(int val):v(val){
        data = new int(val);
        
    }
    A(A& x):v(x.v){
        data = new int(*x.data);
    }
    A& operator=(A& x) {
        *data = *x.data; 
        return *this;
    }
    ~A(){
        delete data;
    }
    A& operator->() {
        *data = *data++; 
        return *this;
    }
    int operator=(int a);
};
int main()
{
    A a1(10);
    cout << "a1's x = " << *a1.data << endl;

    A a2(a1);
    A a3(0);  
    cout << "a3's x = " << *a3.data << endl;  
    //a3 = a1;
    cout << "a2's x = " << *a2.data << endl;
    cout << "a3's x = " << *a3.data << endl;
    *a1.data = 20;
    cout << "a1's x = " << *a1.data << endl;
    cout << "a2's x = " << *a2.data << endl;
    cout << "a3's x = " << *a3.data << endl;

    A& operator+(int a, A& b);

    return 0;
}