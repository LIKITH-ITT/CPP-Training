#include <iostream>
using namespace std;

void subseq(string s, int index, string sub){
    if(index==s.length()){
        cout << sub << endl;
        return;
    }
    subseq(s, index+1,sub);

    subseq(s, index+1,sub + s[index]);
}

int main() {
    string s = "abc";
    subseq(s, 0, "");
    return 0;
}
