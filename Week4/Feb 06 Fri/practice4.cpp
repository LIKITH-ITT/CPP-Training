#include <iostream>
using namespace std;

class A {
public:
    int val;
    int num ;

    A(int x, int y) {
        val = x;
        num = y;
    }

    A(A& a) {
        val = a.val;
        std::cout << a.num << std::endl;
    }
};



int main() {
    A a1(20, 30);
    
    A a2(a1);
    A a3 = a2;
    


    cout << a1.val << std::endl;
  	cout << a2.val << std::endl;
    cout << a2.num << std::endl;
    cout << a3.num << std::endl;
    return 0;
}