#include <iostream>

void onEvent() {
    std::cout << "Event occurred\n";
}

void registerCallback(void (*fp)()) {
    fp();
}

int main() {
    registerCallback(onEvent);
}
