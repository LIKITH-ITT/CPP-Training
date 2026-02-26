#ifndef SYSTEM_H
#define SYSTEM_H

#include "Admin.h"
#include "EmployeeManager.h"
#include "AuthController.h"

class System 
{
private:
    Admin admin;
    EmployeeManager employeeManager;
    AuthController authController;

public:
    System();
    void run();
};
#endif
