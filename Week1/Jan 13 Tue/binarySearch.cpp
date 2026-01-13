#include <iostream>
using namespace std;

int binarySearch(int arr[],int start, int end, int key){
    if(start>=end){
        return -1;
    }
    int mid=(start+end)/2;

    if(arr[mid]==key){
        return mid;
    }
    else if(arr[mid]>key){
        return binarySearch(arr,start, mid,key);
    }
    else{
        return binarySearch(arr,mid+1,end,key);
    }
}

int main(){
    int n, key;

    cout << "Enter the size of the array: ";
    cin >> n;

    int arr[n];
    cout << "Enter the elements of the array: ";
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }

    cout << "Enter the elementt to be searched: ";
    cin >> key;

    cout << "The element is found at index" << binarySearch(arr,0,n,key);
}