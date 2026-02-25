#include <iostream>
using namespace std;

class Logger {
private:
    static int objectCount;
public:
    Logger() {
        objectCount++;
        cout << "Created. Total: " << objectCount << "\n";
    }
    ~Logger() {
        objectCount--;
        cout << "Destroyed. Total: " << objectCount << "\n";
    }
    static int getCount() {
        return objectCount;
    }
};

int Logger::objectCount = 0;
int main() {
    Logger a;
    {
        Logger b;
        Logger c;
    }
    // Logger b;
    // Logger c;
    cout << "Current count: " << Logger::getCount() << "\n";
}