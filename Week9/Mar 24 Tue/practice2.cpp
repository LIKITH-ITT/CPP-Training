#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex m;

void task(int id) {
    if (m.try_lock()) {
        cout << "Thread " << id << " got lock\n";
        this_thread::sleep_for(chrono::milliseconds(100));
        m.unlock();
    } else {
        cout << "Thread " << id << " skipped\n";
    }
}

int main() {
    thread t1(task, 1);
    thread t2(task, 2);

    t1.join();
    t2.join();
}