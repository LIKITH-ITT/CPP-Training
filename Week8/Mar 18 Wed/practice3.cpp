#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Desc {
public:
    bool operator()(int a, int b) {
        return a > b;
    }
};

int main() {
    vector<int> v = {5,1,4,2,3};
    sort(v.begin(), v.end(), Desc());
    // sort(v.begin(), v.end(), [](int a, int b){ return a > b; });

    for(int x : v)
        cout << x << " ";
}