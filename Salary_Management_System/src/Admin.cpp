#include "Admin.h"

Admin::Admin(const std::string& username, const std::string& password) : username(username), password(password) {}

std::string Admin::getUsername() const 
{
    return username; 
}
std::string Admin::getPassword() const {
    return password; 
}

bool Admin::authenticate(const std::string& u, const std::string& p) const 
{
    return username == u && password == p;
}
