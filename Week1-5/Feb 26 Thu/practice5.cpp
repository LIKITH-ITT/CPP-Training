#include <iostream>

class Token {
private:
    Token() {}

    friend Token createToken();
};

Token createToken() {
    return Token();
}

int main() {
    //Token t;  //not possible as it is inaccessible 
    Token t = createToken();
}