#include <iostream>
#include <thread>
#include <string>

void greet(const std::string& name, int times) {
for (int i = 0; i < times; ++i)
std::cout << "Hello, " << name << " (run " << i+1 << ")\n";
}
int main() {
    std::thread t1(greet, "Alice", 3);
    std::thread t2([] {
    std::cout << "Lambda thread id: " << std::this_thread::get_id() << "\n";
    });
    t1.join(); 
    t2.join(); 
    std::cout << "All threads finished.\n";
}