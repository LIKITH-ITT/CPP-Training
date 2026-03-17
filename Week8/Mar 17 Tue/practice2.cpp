#include <iostream>
#include <list>


int main() {
    std::list<int> l = {1,2,3,2,4};
    std::list<int>::iterator it = l.begin();
    std::advance(it, 2);
    l.insert(it, 99); 

    std::cout << "After insert: ";
    for (auto x=l.begin();x!=l.end();++x) 
        std::cout << *x << " ";

    l.erase(it); 
    std::cout << "\nAfter erase: ";
    for (int x : l) 
        std::cout << x << " ";
    l.remove(2);
        std::cout << "\nAfter remove: ";
    for (int x : l) 
        std::cout << x << " ";
}