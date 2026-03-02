#include <iostream>

class Resource
{
public:
    int* data;

    Resource()
    {
        data = new int(100);
    }

    ~Resource()
    {
        delete data;
    }
};

int main()
{
    Resource r1;
    Resource r2 = r1;
}