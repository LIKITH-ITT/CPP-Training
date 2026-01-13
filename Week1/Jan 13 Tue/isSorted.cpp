#include <iostream>
using namespace std;

bool isSorted(int arr[],int start,int n){
    if(start==n-1){
        return true;
    }
    for(int i=start;i<n;i++){
        if(arr[start]>arr[i]){
            return false;
        }
    }
    return isSorted(arr,start+1,n);
}

int main(){
    int n;

    cout << "Enter the size of the array: ";
    cin >> n;

    int arr[n];
    cout << "Enter the elements of the array: ";
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }

    isSorted(arr,0,n)?cout << "The array is sorted" : cout << "The array is not sorted";
}