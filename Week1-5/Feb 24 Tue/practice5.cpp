#include<iostream>
struct Foo {
int val;
Foo(int v) : val(v) { std::cout << "C" << val; }
Foo(const Foo& o) : val(o.val) { std::cout << "X" << val; }
~Foo() { std::cout << "D" << val; }
};
void take(Foo f) {}
int main(){
    Foo a(1);
    Foo& r = a;
    take(r);
    std::cout << '|';
}
