#include <iostream>
#include <map>
using namespace std;

int main() {
    map<int, string> m;

    m[1] = "one";
    m[3] = "three";
    m.insert({2, "two"});
    m.emplace(4, "four");

    cout << "Initial map:\n";
    for (pair<const int,string> p : m)
        cout << p.first << " -> " << p.second << endl;

    cout << "\nAccess m[2]: " << m[2] << endl;

    cout << "Access m[10]: " << m[10] << endl;
        for (pair<const int,string> p : m)
        cout << p.first << " -> " << p.second << endl;

    try {
        cout << "m.at(5): " << m.at(5) << endl;
    } catch (...) {
        cout << "Key not found\n";
    }

    auto it = m.find(2);
    if (it != m.end())
        cout << "\nFound key 2: " << it->second << endl;

    cout << "Count of key 5: " << m.count(5) << endl;

    auto lb = m.lower_bound(2);
    auto ub = m.upper_bound(2);

    cout << "\nlower_bound(2): " << lb->first << endl;
    cout << "upper_bound(2): " << ub->first << endl;

    auto range = m.equal_range(2);
    cout << "equal_range(2): ";
    cout << range.first->first << " to " << range.second->first << endl;

    m.erase(3);  
    m.erase(10);
    cout << "\nAfter erase key 3:\n";
    for (auto p : m)
        cout << p.first << " -> " << p.second << endl;

    cout << "\nSize: " << m.size() << endl;
    cout << "Empty: " << m.empty() << endl;

    cout << "\nReverse order:\n";
    for (auto it = m.rbegin(); it != m.rend(); ++it)
        cout << it->first << " -> " << it->second << endl;

    m.insert_or_assign(2, "TWO");
    cout << "\nAfter insert_or_assign:\n";
    for (auto p : m)
        cout << p.first << " -> " << p.second << endl;
    m.clear();
    cout << "After clear, empty: " << m.empty() << endl;

    return 0;
}