#include <iostream>
#include <cstring>

class Person
{
    char* name;
public:
    Person(const char* n)
    {
        name = new char[strlen(n)];
        strcpy(name, n);
    }

    ~Person()
    {
        delete[] name;
    }

    void print()
    {
        std::cout << name << std::endl;
    }
};

int main()
{
    Person p1("Likith");
    Person p2 = p1;
    p2.print();
}