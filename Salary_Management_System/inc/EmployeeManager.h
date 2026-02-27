#ifndef EMPLOYEEMANAGER_H
#define EMPLOYEEMANAGER_H

#include <string>
#include "Employee.h"
#include "Constants.h"

class EmployeeManager {
private:
    Employee** employees;
    int size;
    int capacity;
    int nextEmployeeID;

    void resize();   
    void shrink();  
public:
    EmployeeManager();
    ~EmployeeManager();

    bool addEmployee(std::string& name, std::string& dob,
                    std::string& email, std::string& phone,
                    std::string& department, std::string& position,
                    double basicSalary, std::string& password);

    bool updateEmployee(std::string& employeeID);
    bool deleteEmployee(std::string& employeeID);

    Employee* findByID(std::string& employeeID)  ;
    Employee* findByEmail(std::string& email)    ;

    Employee* authenticate(std::string& employeeID, std::string& password) ;

    void displayAllEmployees() ;
    void displayAllSalaries() ;
    void displayDetails(Employee& emp);
    void displaySalaryInfo(Employee& emp);
    void displayLeaveInfo(Employee& emp);

    bool grantAdminAccess(std::string& employeeID);
    bool revokeAdminAccess(std::string& employeeID);

    std::string generateEmployeeID();
    int getTotalEmployees() ;
};

#endif
