#include <iostream>

static int global_static = 10;

int global_normal = 10;

void modify_globals() {
    global_static += 5;
    global_normal += 5;
}

void function_static() {
    static int func_static = 0; 
    func_static++;
    std::cout << "function_static value: " << func_static << std::endl;
}

int& get_function_static() {
    static int func_static = 100;
    return func_static;
}

int main() {
    std::cout << "Initial values\n";
    std::cout << "global_static = " << global_static << std::endl;
    std::cout << "global_normal = " << global_normal << std::endl;

    std::cout << "\nModify globals from main\n";
    modify_globals();

    std::cout << "global_static = " << global_static << std::endl;
    std::cout << "global_normal = " << global_normal << std::endl;

    std::cout << "\nCalling function_static multiple times\n";
    function_static();
    function_static();
    function_static();

    std::cout << "\nChanging function static from main\n";
    int& ref = get_function_static();
    std::cout << "Before change: " << ref << std::endl;

    ref = 500;  
    std::cout << "After change: " << get_function_static() << std::endl;

    return 0;
}
