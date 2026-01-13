#include <iostream>
using namespace std;

int main(){
    int a = 10, b = 5, c = 2;

    int result = a++ + --b * c + (a - b) / c;

    int x = 5, y = 10, z = 15;

    bool res = x < y && y < z || x == z && y > x;

    int l = 5, m = 3, n = 2;

    int r = l & m | n ^ l << 1;

    cout << result << endl << res << endl << r << endl;


}