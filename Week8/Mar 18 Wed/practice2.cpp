#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> v = {1,2,3,4};
    vector<int> result(v.size());

    transform(v.begin(), v.end(), result.begin(), [](int x) {
        return x * x;
    });
    for(int x : result)
        cout << x << " ";
}