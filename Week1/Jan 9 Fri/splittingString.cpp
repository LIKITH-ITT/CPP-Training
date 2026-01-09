#include <iostream>
#include <sstream>
using namespace std;

int main(){
    string s;
    cout << "Enter a sentence: ";
    getline(cin, s);

    stringstream ss(s);
    string word;
    string str[10];
    int i=0;

    while(ss >> word){
        str[i] = word;
        i++;
    }

    for(int j=0; j < i;j++){
        cout << str[j] << endl;
    }

    return 0;

}