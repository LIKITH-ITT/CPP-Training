#include<iostream>
enum class Mode : char
{ 
    ON = 1, 
    OFF = 2 
};
enum class Big : long
{
    A = 1000000000000
};
int main(){
    int option = 1;

    switch(static_cast<Mode>(option)){
        case Mode::ON:std::cout << "ON\n";break;
        case Mode::OFF:std::cout << "OFF\n";break;
    }
    // Mode var = Mode::ON;
    // std::cout << static_cast<int>(var) << "\n";
    std::cout << sizeof(Mode);
}