#include <bits/stdc++.h>
using namespace std;

class Func {
public:
    
    void add(int a, int b) {
        cout << "Integer Sum = " << a + b
        << endl;
    }
    
    void add(int a, int b) const {
        cout << "Float Sum = " << a + b
        << endl ;
    }
};

int main() {
    Func obj;
    
    obj.add(10, 2);

    obj.add(5.3, 6.2);

    return 0;
}