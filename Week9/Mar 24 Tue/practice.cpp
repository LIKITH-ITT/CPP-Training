#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex m;

void increment(int id) {
    for (int i = 0; i < 10; i++) {
        std::lock_guard<std::mutex> lock(m);
        counter++;
        std::cout << id <<"Counter: " << counter << std::endl;
    }
}

int main() {
    std::thread t1(increment, 1);
    std::thread t2(increment, 2);

    t1.join();
    t2.join();
    std::cout << "Counter: " << counter << std::endl;
}