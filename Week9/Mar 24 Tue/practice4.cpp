#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex m1, m2;

void task1() {
    cout << "Task1 entered\n";
    m1.lock();
    this_thread::sleep_for(chrono::milliseconds(100));
    m2.lock();

    cout << "Task1 done\n";

    m1.unlock();
    m2.unlock();
}

void task2() {
    cout << "Task2 entered\n";
    m1.lock();
    this_thread::sleep_for(chrono::milliseconds(100));
    m2.lock();

    cout << "Task2 done\n";

    m1.unlock();
    m2.unlock();
}

int main() {
    thread t1(task1);
    thread t2(task2);

    t1.join();
    t2.join();
}