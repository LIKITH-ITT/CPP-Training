#include <iostream>
#include <string>

class ArrayException
{
private:
	std::string error;

public:
	ArrayException(std::string error)
		: error{ error }
	{
	}

	const std::string& getError() const {
        return error; 
    }
};

class IntArray
{
private:
	int data[3]{};

public:
	IntArray() {}

	int getLength() const {
        return 3; 
    }

	int& operator[](const int index)
	{
		if (index < 0 || index >= getLength())
			throw ArrayException{ "Invalid index" };

		return data[index];
	}
    void setData(int value, int index){
        if (value<0)
            throw ArrayException("Can't set value to less than 0");
        data[index] = value;
    }

};

int main()
{
	IntArray array;

	try
	{
		int value = array[2]; //range exception
        array.setData(-1,2); //value exception

	}
	catch (const ArrayException& exception)
	{
		std::cerr << "An array exception occurred (" << exception.getError() << ")\n";
	}
    std::cout << "Continued\n";
}