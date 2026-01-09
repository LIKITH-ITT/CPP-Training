#include<iostream>
using namespace std;

int main(){
    int n;

    cout << "Enter the no. of elements: ";
    cin >> n;

    int arr[n];
    
    for ( int i = 0; i < n; i++){
        cin >> arr[i];
    }

    int largest=0, secondLargest=0;
    for( int i = 0; i < n; i++){
        if(arr[i] > largest){
            secondLargest = largest;
            largest = arr[i];
        }
        else if (arr[i] <= largest && arr[i] > secondLargest){
            secondLargest = arr[i];
        }
    }

    cout << "Second largest no. is " << secondLargest << endl;

    return 0;


}