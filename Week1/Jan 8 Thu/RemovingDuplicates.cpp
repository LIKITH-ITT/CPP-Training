#include<iostream>
using namespace std;

int main(){
    int n;
    
    cout << "Enter the no. of elements: ";
    cin >> n;

    int arr[n];

    cout << "Enter the array elements: ";
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }

    for (int i = 0; i< n - 1; i++){
        for(int j = i + 1; j < n; j++){
            if (arr[i] == arr[j]){
                arr[j] = -1;
            }
        }
    }

    cout << "Array after removing duplicates: ";
    for (int i = 0; i < n; i++){
        if(arr[i] != -1){
            cout << arr[i] << " ";
        }
    }
     return 0;
}