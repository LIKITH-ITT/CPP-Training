#ifndef ADMINCONTROLLER_H
#define ADMINCONTROLLER_H

#include "Admin.h"
#include "Employee.h"
#include "EmployeeManager.h"

class AdminController {
private:
    Admin& admin;
    EmployeeManager& employeeManager;
    Employee* sessionEmployee; 

    void handleAddEmployee();
    void handleViewEmployees();
    void handleUpdateEmployee();
    void handleDeleteEmployee();
    void handleViewSalaries();
    void handleGrantAdminAccess();
    void handleRevokeAdminAccess();

public:
    AdminController(Admin& admin, EmployeeManager& employeeManager, Employee* sessionEmployee = nullptr);
    void run();
};

#endif
