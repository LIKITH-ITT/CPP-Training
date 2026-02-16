#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <regex>
#include <cctype>
#include "Constants.h"

class Validator 
{
public:
    static bool isValidEmail(const std::string& email) 
    {
        std::regex pattern(R"(^[a-zA-Z0-9._]+@[a-zA-Z0-9-]+\.com$)");
        return std::regex_match(email, pattern);
    }
    
    static bool isValidName(const std::string& name) 
    {
        if (name.length() < Constants::MIN_NAME_LENGTH || name.length() > Constants::MAX_NAME_LENGTH) 
        {
            return false;
        }
        
        for (char c : name) 
        {
            if (!std::isalpha(c) && c != ' ') 
            {
                return false;
            }
        }
        
        bool hasAlpha = false;
        for (char c : name) {
            if (std::isalpha(c)) 
            {
                hasAlpha = true;
                break;
            }
        }
        
        return hasAlpha;
    }
    
    static bool isValidPassword(const std::string& password) 
    {
        if (password.length() < Constants::MIN_PASSWORD_LENGTH || password.length() > Constants::MAX_PASSWORD_LENGTH) 
        {
            return false;
        }
        
        bool hasUpper = false, hasLower = false, hasDigit = false;
        
        for (char c : password) 
        {
            if (std::isupper(c)) hasUpper = true;
            if (std::islower(c)) hasLower = true;
            if (std::isdigit(c)) hasDigit = true;
        }
        
        return hasUpper && hasLower && hasDigit;
    }
    
    static bool isValidAmount(double amount) 
    {
        return amount > 0;
    }
    
    static bool isValidAccountNumber(long long accNum) 
    {
        return accNum >= Constants::INITIAL_ACCOUNT_NUMBER;
    }
    
    static bool isValidUsername(const std::string& username) 
    {
        if (username.empty() || username.length() > 20) {
            return false;
        }
        
        for (char c : username) 
        {
            if (!std::isalnum(c) && c != '_') 
            {
                return false;
            }
        }
        
        return true;
    }
};

#endif
