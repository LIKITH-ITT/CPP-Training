#include <iostream>
#include <thread>
#include<mutex>
#include<condition_variable>

class Semaphore
{
    std::mutex m;
    std::condition_variable cv;
    int count;
    public:
    Semaphore(int count): count(count){}

    void acquire()
    {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [&] {return count>0;});
        count--;
    }

    void release()
    {
        std::unique_lock<std::mutex> lock(m);
        count++;
        cv.notify_one();
    }
};
Semaphore sem(2);

void task(int id) {
    sem.acquire();

    std::cout << "Thread " << id << " entered\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Thread " << id << " leaving\n";

    sem.release();
}



int main() {
    std::thread t1(task, 1);
    std::thread t2(task, 2);
    std::thread t3(task, 3);

    t1.join();
    t2.join();
    t3.join();
}