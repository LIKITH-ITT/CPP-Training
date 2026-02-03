#include <iostream>
using namespace std;

class Person
{
private:
    int age;

public:
    void setAge(int a)
    {
        age = a;
    }

    int getAge()
    {
        return age;
    }
};

int main()
{
    Person p;
    p.setAge(25);
    cout << p.getAge() << endl;
}
