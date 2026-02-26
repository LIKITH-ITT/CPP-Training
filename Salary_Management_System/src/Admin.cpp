#include "Admin.h"

Admin::Admin(const std::string& username, const std::string& password) : username(username), password(password) {}

std::string Admin::getUsername()
{
    return username; 
}
std::string Admin::getPassword()
{
    return password; 
}

bool Admin::authenticate(std::string& u, std::string& p)
{
    return username == u && password == p;
}
