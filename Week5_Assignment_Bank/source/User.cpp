#include "User.h"

User::User(const long id, const std::string& pwd) 
{
    _userID = id;
    _password = pwd;
}

User::~User() {}

long User::getUserID()  
{
    return _userID;
}

std::string User::getPassword() 
{
    return _password;
}

void User::setPassword( std::string& newPassword) 
{
    _password = newPassword;
}

bool User::authenticate( std::string& inputPassword)  
{
    return _password == inputPassword;
}
