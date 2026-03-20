#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> a = {1,2,3};
    vector<int> b = {4,5,6};
    vector<int> result(3);

    transform(a.begin(), a.end(), b.begin(), result.begin(),
        [](int x, int y) {
            return x + y;
        });

    for(int x : result)
        cout << x << " ";
}