#include <thread>
#include <chrono>
#include <iostream>
void worker(int id) {
    std::cout << "Thread " << id << " OS-id=" << std::this_thread::get_id() << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}
int main() {
    std::thread t1(worker, 1);
    //t1.join();
    std::thread t2(worker, 2);
    t1.join();
     t2.join();
}