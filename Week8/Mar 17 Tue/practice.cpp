#include <iostream>
#include <vector>
#include<algorithm>

class A {
public:
    A(int x, int y) {
        std::cout << "Constructor\n";
    }

    A(const A&) {
        std::cout << "Copy\n";
    }
};

int main() {
    std::vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(50);
    v.push_back(60);
    //v.pop();

    std::cout << "Elements: ";
    for (int x : v) std::cout << x << " ";

    std::cout << "\nSize: " << v.size();
    std::cout << "\nCapacity: " << v.capacity();
    std::cout << "\nMax Size: " << v.max_size();
    std::cout << "\nEmpty: " << v.empty();
    std::cout << "\n"<<v.data();

    std::vector<int> v1;

    v1.reserve(5);
    std::cout << "\nAfter reserve → Size: " << v1.size() << " Capacity: " << v1.capacity() << std::endl;

    v1.resize(5);
    std::cout << "After resize → Size: " << v1.size() << " Capacity: " << v1.capacity() << std::endl;
    std::cout << "\nMax Size: " << v1.max_size();

    std::vector<A> obj;

    obj.push_back(A(1,2));
    obj.emplace_back(1,2);
    std::remove(v.begin(),v.end(),20);
    std::cout << "Elements: ";
    for (int x : v) std::cout << x << " ";

}