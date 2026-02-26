#ifndef EMPLOYEECONTROLLER_H
#define EMPLOYEECONTROLLER_H

#include "Employee.h"
#include "EmployeeManager.h"

class EmployeeController {
private:
    Employee& employee;
    EmployeeManager& employeeManager;

    void handleViewDetails();
    void handleViewLeaveBalance();
    void handleViewSalary();
    void handleRecordLeaves();

public:
    EmployeeController(Employee& emp, EmployeeManager& em);
    void run();
};

#endif
