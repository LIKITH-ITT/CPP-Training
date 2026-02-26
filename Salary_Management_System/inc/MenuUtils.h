#ifndef MENUUTILS_H
#define MENUUTILS_H

#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include "Constants.h"
#include "UIStrings.h"

namespace MenuUtils 
{

    inline void displaySeparator() 
    {
        std::cout << UIStrings::SEPARATOR;
    }

    inline void displayHeader(const char* title) 
    {
        std::cout << UIStrings::NEWLINE;
        displaySeparator();
        std::cout << "    " << title << UIStrings::NEWLINE;
        displaySeparator();
    }

    inline void displayMainMenu() 
    {
        displayHeader(UIStrings::TITLE_SYSTEM);
        std::cout << UIStrings::MENU_MAIN_LOGIN;
        std::cout << UIStrings::MENU_MAIN_EXIT;
        displaySeparator();
        std::cout << UIStrings::PROMPT_CHOICE;
    }

    inline void displayAdminMenu() 
    {
        displayHeader(UIStrings::TITLE_ADMIN_PANEL);
        std::cout << UIStrings::MENU_ADMIN_ADD;
        std::cout << UIStrings::MENU_ADMIN_VIEW;
        std::cout << UIStrings::MENU_ADMIN_UPDATE;
        std::cout << UIStrings::MENU_ADMIN_DELETE;
        std::cout << UIStrings::MENU_ADMIN_SALARY;
        std::cout << UIStrings::MENU_ADMIN_GRANT;
        std::cout << UIStrings::MENU_ADMIN_REVOKE;
        std::cout << UIStrings::MENU_ADMIN_LOGOUT;
        displaySeparator();
        std::cout << UIStrings::PROMPT_CHOICE;
    }

    inline void displayEmployeeMenu() 
    {
        displayHeader(UIStrings::TITLE_EMP_PANEL);
        std::cout << UIStrings::MENU_EMP_DETAILS;
        std::cout << UIStrings::MENU_EMP_LEAVE;
        std::cout << UIStrings::MENU_EMP_SALARY;
        std::cout << UIStrings::MENU_EMP_RECORD;
        std::cout << UIStrings::MENU_EMP_LOGOUT;
        displaySeparator();
        std::cout << UIStrings::PROMPT_CHOICE;
    }

    inline void displayRoleSelectionMenu() 
    {
        displayHeader(UIStrings::TITLE_ROLE_SELECT);
        std::cout << UIStrings::MENU_ROLE_ADMIN;
        std::cout << UIStrings::MENU_ROLE_EMP;
        std::cout << UIStrings::MENU_ROLE_LOGOUT;
        displaySeparator();
        std::cout << UIStrings::PROMPT_CHOICE;
    }

inline int getMenuChoice(int minVal, int maxVal)
{
    std::string input;

    while (true)
    {
        std::getline(std::cin, input);

        std::istringstream iss(input);
        int choice;
        char extra;

        if (iss >> choice && !(iss >> extra) &&
            choice >= minVal && choice <= maxVal)
        {
            return choice;
        }

        std::cout << UIStrings::ERR_INVALID_CHOICE
                  << minVal << "-" << maxVal << ": ";
    }
}

}

#endif
