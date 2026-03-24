
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex m1, m2;

void task1() {
    unique_lock<mutex> l1(m1, defer_lock);
    unique_lock<mutex> l2(m2, defer_lock);
    cout << "Task1 entered\n";
    std::lock(l1,l2);
    this_thread::sleep_for(chrono::milliseconds(100));

    cout << "Task1 done\n";

}

void task2() {
    unique_lock<mutex> l1(m1, defer_lock);
    unique_lock<mutex> l2(m2, defer_lock);
    cout << "Task2 entered\n";
    std::lock(l1,l2);
    this_thread::sleep_for(chrono::milliseconds(100));

    cout << "Task2 done\n";

}

int main() {
    thread t1(task1);
    thread t2(task2);

    t1.join();
    t2.join();
}