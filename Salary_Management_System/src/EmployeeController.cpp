#include "EmployeeController.h"
#include "Constants.h"
#include "MenuUtils.h"
#include "InputValidator.h"
#include "UIStrings.h"
#include "Logger.h"
#include <iostream>

EmployeeController::EmployeeController(Employee& emp, EmployeeManager& em) : employee(emp), employeeManager(em) {}

void EmployeeController::run() 
{
    bool active = true;
    while (active) 
    {
        MenuUtils::displayEmployeeMenu();
        EmployeeMenuOption choice = static_cast<EmployeeMenuOption>(MenuUtils::getMenuChoice(1, 5));

        switch (choice) 
        {
            case EmployeeMenuOption::VIEW_DETAILS:
                handleViewDetails();
                break;
            case EmployeeMenuOption::VIEW_LEAVE:
                handleViewLeaveBalance();
                break;
            case EmployeeMenuOption::VIEW_SALARY:
                handleViewSalary();
                break;
            case EmployeeMenuOption::RECORD_LEAVES:
                handleRecordLeaves();
                break;
            case EmployeeMenuOption::LOGOUT:
                Logger::info("Employee " + employee.getEmployeeID() + " logged out.");
                active = false;
                break;
        }
    }
}

void EmployeeController::handleViewDetails() 
{
    MenuUtils::displayHeader(UIStrings::HEADER_MY_DETAILS);
    employeeManager.displayDetails(employee);
}

void EmployeeController::handleViewLeaveBalance() 
{
    MenuUtils::displayHeader(UIStrings::HEADER_MY_LEAVE);
    employeeManager.displayLeaveInfo(employee);
}

void EmployeeController::handleViewSalary() 
{
    MenuUtils::displayHeader(UIStrings::HEADER_MY_SALARY);
    employeeManager.displaySalaryInfo(employee);
}

void EmployeeController::handleRecordLeaves() 
{
    MenuUtils::displayHeader(UIStrings::HEADER_RECORD_LEAVES);
    std::cout << UIStrings::CURR_LEAVES_TAKEN << employee.getLeavesTaken() << "\n";
    std::cout << UIStrings::ALLOC_LEAVES_LABEL << ALLOCATED_LEAVES << "\n\n";

    int newLeaves = InputValidator::getValidatedInt(UIStrings::INPUT_LEAVES, 0, WORKING_DAYS);

    employee.setLeavesTaken(newLeaves);
    Logger::info("Leaves updated for " + employee.getEmployeeID() + ": " + std::to_string(newLeaves));
}
