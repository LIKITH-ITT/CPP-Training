#include <iostream>
using namespace std;

enum class Day
{
    Sunday = 1,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

int main()
{
    Day today = Day::Thursday;

    cout << static_cast<int>(today);
    
    return 0;
}