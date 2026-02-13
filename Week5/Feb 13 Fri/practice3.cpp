#include<iostream>
class A
{
public:
	virtual std::string getName() const { return "A"; }
};

class B : public A
{
public:
	std::string getName() const override final { return "B"; } //overrides A::getName()
};

class C : public B
{
public:
	//std::string getName() const override { return "C"; } //compile error: overrides B::getName() which is final
};