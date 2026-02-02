#include <iostream>

int global_init = 10;          // Data segment
int global_uninit;             // BSS segment

void func()
{
    static int static_var = 5; // Data segment
    int local_var = 20;        // Stack

    int* heap_var = new int(30); // Heap

    std::cout << "static_var = " << static_var << '\n';
    std::cout << "local_var  = " << local_var << '\n';
    std::cout << "*heap_var  = " << *heap_var << '\n';

    delete heap_var; // Proper cleanup
}

int main()
{
    func();
    return 0;
}
