#include<iostream>
#include<vector>
#include<algorithm>

class CompareReference
{
    int reference;
public:
    CompareReference(int ref):reference(ref){}
    bool operator()(int a, int b)
    {
        return abs(a-reference) < abs(b-reference);
    }
};

int main()
{
    std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    sort(v.begin(),v.end(),CompareReference(5));
    for (int x : v)
    std::cout << x << " ";
}