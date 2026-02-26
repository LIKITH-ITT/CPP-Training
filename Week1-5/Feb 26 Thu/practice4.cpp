#include <iostream>

class Secret {
private:
    int value = 42;

    friend class Friend;
};

class Friend {
public:
    void change(Secret& s) {
        s.value = 999;
    }
};

int main() {
    Secret s;
    Friend h;
    h.change(s);
}