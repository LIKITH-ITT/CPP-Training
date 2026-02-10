#include <iostream>
using namespace std;
 
void modifyValue(int &x) {
   x = x + 10;
}
 
int main() {
   int a = 5;
   modifyValue(a);
   cout << "Value of a: " << a << endl;
   return 0;
}