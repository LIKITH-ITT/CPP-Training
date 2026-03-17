#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
unordered_set<int> s = {10,1,7,3,20};
    for(int x : s)
        cout << x << " ";
}