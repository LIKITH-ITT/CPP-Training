#ifndef ADMIN_H
#define ADMIN_H
#include <string>

class Admin {
private:
    std::string username;
    std::string password;

public:
    Admin(const std::string& username, const std::string& password);

    std::string getUsername() const;
    std::string getPassword() const;

    bool authenticate(const std::string& username,const std::string& password) const;
};

#endif
