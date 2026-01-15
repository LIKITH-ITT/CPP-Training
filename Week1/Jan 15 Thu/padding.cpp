#include <iostream>
#include <cstddef>   // offsetof

// 1️⃣ Default padding (compiler decides)
struct DefaultPadding {
    char e;
    int a;// 4 bytes (alignment)
    char c;
    int  i;
    double d;
};

// 2️⃣ Reordered members (best portable way)
struct Reordered {
    double d;
    int  i;
    char c;
    char e;
};

// 3️⃣ Using alignas (standard, portable)
struct alignas(1) AlignasPacked {
    double d;
    int  i;
    char c;
    char e;
};

// 4️⃣ Compiler-specific packing (GCC / Clang)
#if defined(__GNUC__)
struct __attribute__((packed)) PackedGCC {
    double d,s;
    int  i;
    char c;
    char e;
};
#endif

// 5️⃣ MSVC packing
#if defined(_MSC_VER)
#pragma pack(push, 1)
struct PackedMSVC {
    double d;
    int  i;
    char c;
    char e;
};
#pragma pack(pop)
#endif

int main() {
    std::cout << "DefaultPadding size:  " << sizeof(DefaultPadding) << '\n';
    std::cout << "Reordered size:       " << sizeof(Reordered) << '\n';
    std::cout << "AlignasPacked size:   " << sizeof(AlignasPacked) << '\n';

#if defined(__GNUC__)
    std::cout << "PackedGCC size:       " << sizeof(PackedGCC) << '\n';
#endif

#if defined(_MSC_VER)
    std::cout << "PackedMSVC size:      " << sizeof(PackedMSCV) << '\n';
#endif

return 0;
}
    
