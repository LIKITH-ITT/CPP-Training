#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<pair<int,int>> v = {{1,2}, {3,1}, {2,5}};
    sort(v.begin(), v.end(), [](pair<int,int> a, pair<int,int> b) {
        return a.second < b.second;
    });
    for(auto p : v)
        cout << "(" << p.first << "," << p.second << ") ";
}