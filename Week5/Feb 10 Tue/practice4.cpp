class Base {
public:
    // Base(int x) {}
    Base(){}
};
 
class D1 : public Base
{
    public:
    D1(){}
};

class D2 : public Base
{
    public:
    D2(){}
};

class DD : public D1, D2
{
    public:
    DD(){}
};

DD obj;