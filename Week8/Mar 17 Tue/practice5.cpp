#include<iostream>
#include<unordered_map>
using namespace std;
int main(){
unordered_map<int, int> m;

cout << m.bucket_count() << endl;

for(int i = 0; i < 50; i++){
    m[i] = i;
    cout << m.bucket_count() << endl;
}

cout << m.bucket_count() << endl;
    size_t hash_value = hash<int>()(25);

    cout << "Hash: " << hash_value << endl;

    for(auto it=m.begin();it!=m.end();++it){
        cout << it->first << "->" << it->second << "\n";
    }
}