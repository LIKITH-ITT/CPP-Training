#ifndef ADMIN_H
#define ADMIN_H
#include <string>

class Admin {
private:
    std::string username;
    std::string password;

public:
    Admin(const std::string& username, const std::string& password);

    std::string getUsername() ;
    std::string getPassword() ;

    bool authenticate( std::string& username, std::string& password) ;
};

#endif
