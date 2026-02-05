#include <iostream>

int main(){

    char c = 'a';
    char* a = "a";
    char* b = &c;
    int i = 10;
    int& r = i;
    int* ip = &i;
    int*& ref = ip;
    int* cal = (int*)calloc(1,sizeof(int));
}