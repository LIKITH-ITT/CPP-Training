#include <iostream>
using namespace std;
struct num
{
    int x, y;
};

int main()
{
    num p = {23, 34};

    cout << p.x << " ";
    cout << p.y << endl;

    p.x = 879;

    cout << p.x << " ";
    cout << p.y;

    return 0;
}