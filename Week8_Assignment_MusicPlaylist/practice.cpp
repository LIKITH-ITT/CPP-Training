#include <iostream>       
#include <thread>        
 
void foo() 
{
    std::cout << "A\n";
    std::cout << "B\n";

}

void bar(int x)
{
    std::cout << "1\n";
    std::cout << "2\n";

}

int main() 
{
    std::thread first (foo);     
    std::thread second (bar,0); 

    std::cout << "main, foo and bar now execute concurrently...\n";

  
    second.join();
    //first.join();

    std::cout << "foo and bar completed.\n";

    return 0;
}