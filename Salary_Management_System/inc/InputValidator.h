#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <iostream>
#include <string>
#include <limits>
#include <regex>

namespace InputValidator 
{

    inline bool isValidLength(const std::string& input, int min, int max) 
    {
        int length = input.length();
        return length >= min && length <= max;
    }

    inline bool isValidEmail(const std::string& email) 
    {
        std::regex pattern(R"(^[a-zA-Z0-9._%+\-]+@[a-zA-Z0-9.\-]+\.com$)");
        return std::regex_match(email, pattern);
    }

    inline bool isValidPhone(const std::string& phone) 
    {
        std::regex pattern(R"(^\+?[0-9]{10,15}$)");
        return std::regex_match(phone, pattern);
    }

    inline bool isValidPassword(const std::string& password)
    {
        bool isValid = true;
        if (!isValidLength(password, 6, 30)) 
            isValid = false;
        bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
        for (char c : password)
        {
            if (std::isupper(c))  hasUpper   = true;
            if (std::islower(c))  hasLower   = true;
            if (std::isdigit(c))  hasDigit   = true;
            if (std::ispunct(c))  hasSpecial = true;
        }
        isValid = hasUpper && hasLower && hasDigit && hasSpecial;
        return isValid;
    }

    inline bool isPositiveDouble(double value) 
    {
        return value > 0.0;
    }

    inline bool isPositiveInt(int value) 
    {
        return value > 0;
    }

    inline bool isValidDate(const std::string& dob) 
    {
        std::regex pattern(R"(^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/(1[0-9]{3}|2[0-9]{3})$)");
        return std::regex_match(dob, pattern);
    }

    inline bool isValidName(const std::string& name) 
    {
        bool isValid = true;
        if (!isValidLength(name, 2, 50)) 
            isValid = false;
        for (char c : name) 
        {
            if (!isalpha(c) && c != ' ') 
                isValid = false;
        }
        return isValid;
    }

    inline std::string getValidatedString(const std::string& prompt, int minLen, int maxLen) 
    {
        std::string input;
        while (true) 
        {
            std::cout << prompt;
            std::getline(std::cin, input);
            if (!input.empty() && isValidLength(input, minLen, maxLen)) 
                return input;
            std::cout << "  [!] Input must be " << minLen << "-" << maxLen << " characters. Try again.\n";
        }
    }

    inline int getValidatedInt(const std::string& prompt, int minVal, int maxVal)
    {
        int value;

        while (true)
        {
            std::cout << prompt;

            if (std::cin >> value &&
                std::cin.peek() == '\n' &&
                value >= minVal && value <= maxVal)
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "  [!] Enter a number between " << minVal << " and " << maxVal << ". Try again.\n";
        }
    }
    inline double getValidatedDouble(const std::string& prompt, double minVal, double maxVal)
    {
        double value;

        while (true)
        {
            std::cout << prompt;

            if (std::cin >> value &&
                std::cin.peek() == '\n' &&
                value >= minVal && value <= maxVal)
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "  [!] Enter a number between " << minVal << " and " << maxVal << ". Try again.\n";
        }
    }

    inline std::string getValidatedEmail(const std::string& prompt) 
    {
        std::string input;
        while (true) 
        {
            std::cout << prompt;
            std::getline(std::cin, input);
            if (isValidEmail(input)) 
                return input;
            std::cout << "  [!] Invalid email format. Try again.\n";
        }
    }

    inline std::string getValidatedPhone(const std::string& prompt) 
    {
        std::string input;
        while (true) 
        {
            std::cout << prompt;
            std::getline(std::cin, input);
            if (isValidPhone(input)) 
                return input;
            std::cout << "  [!] Invalid phone. Must be 10-15 digits. Try again.\n";
        }
    }

    inline std::string getValidatedPassword(const std::string& prompt) 
    {
        std::string input;
        while (true) 
        {
            std::cout << prompt;
            std::getline(std::cin, input);
            if (isValidPassword(input)) 
                return input;
            std::cout << "  [!] Password must be 6-30 characters and contain uppercase, lowercase, digit, and special character.\n";        
        }
    }

    inline std::string getValidatedDate(const std::string& prompt) 
    {
        std::string input;
        while (true) 
        {
            std::cout << prompt;
            std::getline(std::cin, input);
            if (isValidDate(input)) 
                return input;
            std::cout << "  [!] Invalid date. Use DD/MM/YYYY format. Try again.\n";
        }
    }

    inline std::string getValidatedName(const std::string& prompt) 
    {
        std::string input;
        while (true) 
        {
            std::cout << prompt;
            std::getline(std::cin, input);
            if (isValidName(input)) 
                return input;
            std::cout << "  [!] Name must be 2-50 letters only. Try again.\n";
        }
    }

}

#endif
