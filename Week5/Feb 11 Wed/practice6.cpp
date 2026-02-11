
#include <iostream>

class Base
{
public:
	int m_value{};
};

class Derived : public Base
{
private:
	using Base::m_value;

public:
	Derived(int value) : Base { value }
	{
	}
};

int main()
{
	Derived derived{ 7 };
	//std::cout << derived.m_value; //error

	Base& base{ derived };
	std::cout << base.m_value; 

	return 0;
}