#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include "Admin.h"
#include "Employee.h"
#include "EmployeeManager.h"

class AuthController {
private:
    Admin& admin;
    EmployeeManager& employeeManager;

    Employee* performLogin(bool& isAdminLogin);

    void handleDualAccessLogin(Employee* emp);

public:
    AuthController(Admin& admin, EmployeeManager& em);
    void run();
};

#endif
