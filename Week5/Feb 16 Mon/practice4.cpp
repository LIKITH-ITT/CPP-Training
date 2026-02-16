#include<iostream>
class A{
    int x;
    friend int getX(A& obj);
};

int getX(A& obj){
    return obj.x;

}
int main(){
    A a;
    int x = getX(a);
    std::cout << x;
}