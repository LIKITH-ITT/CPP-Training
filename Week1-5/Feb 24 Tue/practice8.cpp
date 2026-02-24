#include<iostream>

int main(){

int arr[5] = {10, 20, 30, 40, 50};
int* end = arr + 3; 
std::cout << *end;

int arr[5] = {1, 2, 3, 4, 5};
int sum = 0;
for (int* p = arr; p != arr + 5; ++p) {
sum += *p;
}
std::cout << sum << std::endl;

}

