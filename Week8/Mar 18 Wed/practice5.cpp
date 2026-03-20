#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class GreaterThan {
    int x;
public:
    int calls;

    GreaterThan(int val) : x(val), calls(0) {}

    bool operator()(int n) {
        calls++;
        return n > x;
    }
};

int main() {
    vector<int> v = {1,5,7,2,9,3};
    GreaterThan gt(5);
    int count = count_if(v.begin(), v.end(), gt);
    cout << "Count: " << count << endl;
    cout << "Calls: " << gt.calls << endl;
}