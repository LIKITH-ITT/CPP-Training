#include "AdminController.h"
#include "Constants.h"
#include "MenuUtils.h"
#include "InputValidator.h"
#include "UIStrings.h"
#include "Logger.h"
#include <iostream>

AdminController::AdminController(Admin& admin, EmployeeManager& em, Employee* sessionEmployee)
: admin(admin), employeeManager(em), sessionEmployee(sessionEmployee) {}

void AdminController::run() 
{
    bool isRunning = true;
    while (isRunning) 
    {
        MenuUtils::displayAdminMenu();
        AdminMenuOption choice = static_cast<AdminMenuOption>(MenuUtils::getMenuChoice(1, 8));

        switch (choice) 
        {
            case AdminMenuOption::ADD_EMPLOYEE:
                handleAddEmployee();       
                break;
            case AdminMenuOption::VIEW_EMPLOYEES:
                handleViewEmployees();     
                break;
            case AdminMenuOption::UPDATE_EMPLOYEE: 
                handleUpdateEmployee();    
                break;
            case AdminMenuOption::DELETE_EMPLOYEE: 
                handleDeleteEmployee();    
                break;
            case AdminMenuOption::VIEW_SALARIES:   
                handleViewSalaries();      
                break;
            case AdminMenuOption::GRANT_ADMIN:     
                handleGrantAdminAccess();  
                break;
            case AdminMenuOption::REVOKE_ADMIN:    
                handleRevokeAdminAccess(); 
                break;
            case AdminMenuOption::LOGOUT:
                Logger::info("Admin logged out.");
                isRunning = false;
                break;
        }
    }
}

void AdminController::handleAddEmployee() 
{
    MenuUtils::displayHeader(UIStrings::HEADER_ADD_EMP);

    std::string name = InputValidator::getValidatedName(UIStrings::INPUT_NAME);
    std::string dob = InputValidator::getValidatedDate(UIStrings::INPUT_DOB);
    std::string email = InputValidator::getValidatedEmail(UIStrings::INPUT_EMAIL);
    std::string phone = InputValidator::getValidatedPhone(UIStrings::INPUT_PHONE);
    std::string department = InputValidator::getValidatedString(UIStrings::INPUT_DEPT, 2, 50);
    std::string position = InputValidator::getValidatedString(UIStrings::INPUT_POSITION, 2, 50);
    double salary = InputValidator::getValidatedDouble(UIStrings::INPUT_SALARY, 1.0, 9999999.0);
    std::string password = InputValidator::getValidatedPassword(UIStrings::INPUT_PASSWORD);

    employeeManager.addEmployee(name, dob, email, phone, department, position, salary, password);

}

void AdminController::handleViewEmployees() 
{
    MenuUtils::displayHeader(UIStrings::HEADER_ALL_EMP);
    employeeManager.displayAllEmployees();
    std::cout << UIStrings::MSG_TOTAL_EMP << employeeManager.getTotalEmployees() << UIStrings::MSG_TOTAL_EMP_SUFFIX;
}

void AdminController::handleUpdateEmployee() 
{
    MenuUtils::displayHeader(UIStrings::HEADER_UPDATE_EMP);
    std::string id = InputValidator::getValidatedString(UIStrings::PROMPT_EMP_ID, 1, 10);

    employeeManager.updateEmployee(id);
}

void AdminController::handleDeleteEmployee() 
{
    MenuUtils::displayHeader(UIStrings::HEADER_DELETE_EMP);
    std::string id = InputValidator::getValidatedString(UIStrings::PROMPT_EMP_ID, 1, 10);

    Employee* emp = employeeManager.findByID(id);
    if (!emp) 
    {
        std::cout << UIStrings::ERR_NOT_FOUND;
        return;
    }

    std::cout << UIStrings::MSG_DELETING << emp->getName() << " (" << id << ")\n";
    std::cout << UIStrings::PROMPT_CONFIRM_DEL;
    char confirm;
    std::cin >> confirm;
    std::cin.ignore();

    if (confirm == 'y' || confirm == 'Y') 
    {
        employeeManager.deleteEmployee(id);
    } 
    else 
    {
        std::cout << UIStrings::ERR_DEL_CANCELLED;
    }
}

void AdminController::handleViewSalaries() 
{
    MenuUtils::displayHeader(UIStrings::HEADER_ALL_SALARIES);
    employeeManager.displayAllSalaries();
}

void AdminController::handleGrantAdminAccess() 
{
    MenuUtils::displayHeader(UIStrings::HEADER_GRANT_ADMIN);
    std::string id = InputValidator::getValidatedString(UIStrings::PROMPT_EMP_ID, 1, 10);

    if (employeeManager.grantAdminAccess(id))
        std::cout << (UIStrings::MSG_GRANT_OK + id);    
    else
        std::cout << UIStrings::ERR_NOT_FOUND;
}

void AdminController::handleRevokeAdminAccess() 
{
    MenuUtils::displayHeader(UIStrings::HEADER_REVOKE_ADMIN);
    std::string id = InputValidator::getValidatedString(UIStrings::PROMPT_EMP_ID, 1, 20);

    if (sessionEmployee != nullptr && sessionEmployee->getEmployeeID() == id) 
    {
        std::cout << UIStrings::ERR_SELF_REVOKE;
        Logger::warning("Self-revoke attempt blocked for: " + id);
        return;
    }

    if (!employeeManager.revokeAdminAccess(id))
        std::cout << UIStrings::ERR_NOT_FOUND;
}