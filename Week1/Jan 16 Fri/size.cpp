#include <iostream>
#include <array>

namespace mynamespace{
    int cout = 0;
}

struct Default {
    char c;
    int i;
};

#pragma pack(push, 1)
struct Packed {
    char c;
    int i;
};
#pragma pack(pop)

int main() {
    std::cout << "Default size: " << sizeof(Default) << '\n';
    std::cout << "Packed size : " << sizeof(Packed) << '\n';

    std::cout << mynamespace::cout << std::endl;
    const int a=5;
    std::cout << sizeof(long) << "\n";
    std::cout << sizeof(long long) << "\n";
    std::array<int, a> arr = {1, 2, 3, 4, 5};
    arr={2,4,5,6,8};
    int b[5] = {1,2,3,4,5};
    b[0]=7;
    //arr.at(6);
    for (int x : b)
    std::cout << x << " ";

    std::cout << b << std::endl;
}
