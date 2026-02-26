#include "AuthController.h"
#include "AdminController.h"
#include "EmployeeController.h"
#include "Constants.h"
#include "MenuUtils.h"
#include "InputValidator.h"
#include "UIStrings.h"
#include "Logger.h"
#include <iostream>

AuthController::AuthController(Admin& admin, EmployeeManager& em) : admin(admin), employeeManager(em) {}

void AuthController::run() 
{
    bool running = true;
    while (running) 
    {
        MenuUtils::displayMainMenu();
        MainMenuOption choice = static_cast<MainMenuOption>(MenuUtils::getMenuChoice(1, 2));

        switch (choice) 
        {
            case MainMenuOption::LOGIN: 
            {
                bool isAdminLogin = false;
                Employee* employee = performLogin(isAdminLogin);

                if (isAdminLogin) 
                {
                    Logger::info("System admin logged in.");
                    AdminController adminControl(admin, employeeManager);
                    adminControl.run();
                } 
                else if (employee != nullptr) 
                {
                    if (employee->getHasAdminAccess())
                        handleDualAccessLogin(employee);
                    else 
                    {
                        Logger::info("Employee logged in: " + employee->getEmployeeID());
                        EmployeeController employeeCtrl(*employee, employeeManager);
                        employeeCtrl.run();
                    }
                } 
                else 
                {
                    std::cout << UIStrings::ERR_LOGIN_FAILED;
                    Logger::warning("Failed login attempt.");
                }
                break;
            }
            case MainMenuOption::EXIT:
                std::cout << UIStrings::MSG_SHUTDOWN;
                running = false;
                break;
        }
    }
}

Employee* AuthController::performLogin(bool& isAdminLogin) 
{
    MenuUtils::displayHeader(UIStrings::TITLE_LOGIN);

    std::string id, password;
    std::cout << UIStrings::PROMPT_ID;
    std::getline(std::cin, id);
    std::cout << UIStrings::PROMPT_PASSWORD;
    std::getline(std::cin, password);

    if (admin.authenticate(id, password)) 
    {
        isAdminLogin = true;
        return nullptr;
    }

    isAdminLogin = false;
    return employeeManager.authenticate(id, password);
}

void AuthController::handleDualAccessLogin(Employee* employee) 
{
    bool sessionActive = true;
    while (sessionActive) 
    {
        MenuUtils::displayRoleSelectionMenu();
        RoleMenuOption choice = static_cast<RoleMenuOption>(MenuUtils::getMenuChoice(1, 3));

        switch (choice) 
        {
            case RoleMenuOption::ADMIN_CONTROLS: 
            {
                Logger::info(employee->getEmployeeID() + " entered admin mode.");
                AdminController adminControl(admin, employeeManager, employee);
                adminControl.run();
                break;
            }
            case RoleMenuOption::EMPLOYEE_CONTROLS: 
            {
                Logger::info(employee->getEmployeeID() + " entered employee mode.");
                EmployeeController employeeCtrl(*employee, employeeManager);
                employeeCtrl.run();
                break;
            }
            case RoleMenuOption::LOGOUT:
                Logger::info(employee->getEmployeeID() + " logged out from dual-access session.");
                sessionActive = false;
                break;
        }
    }
}