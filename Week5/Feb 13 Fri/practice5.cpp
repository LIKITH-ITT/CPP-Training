class A {
private:
    int x = 10;
    friend class B;
};

class B : public A {
};

class C : public B {
public:
    void test(A& a) {
        //std::cout << a.x;  
    }
};
