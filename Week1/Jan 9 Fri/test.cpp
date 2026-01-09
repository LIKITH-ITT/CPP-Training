#include <iostream>
using namespace std;

int main(){
    cout << "cout message..." << endl;//Print stdout and stderr messages seperately in .txt and .log file
    cerr << "cerr message..."  << endl;
    clog << "clog message..." << endl;
    cerr << "cerr message 2 ..." << endl;
    return 0;
}
