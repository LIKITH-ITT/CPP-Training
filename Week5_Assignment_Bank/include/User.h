#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

class User 
{
private:
    long _userID;
    std::string _password;
    
public:
    User(const long id,const std::string& pwd);
    virtual ~User();
    long getUserID();
    std::string getPassword();
    void setPassword(std::string& newPassword);
    bool authenticate(std::string& inputPassword);

    virtual void displayMenu() = 0;
};

#endif
