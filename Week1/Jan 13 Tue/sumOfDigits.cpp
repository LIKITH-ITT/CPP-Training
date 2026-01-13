#include <iostream>
using namespace std;

int sumOfDigits(int n){
    if(n==0){
        return 0;
    }
    int m = n % 10;
    n = n / 10;
    int sum = m + sumOfDigits(n);
    return sum;
}

int main(){
    int n;

    cout << "Enter a number:";
    cin >> n;

    cout << sumOfDigits(n)<< endl;

    return 0;

}