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

    bool addEmployee(const std::string& name, const std::string& dob,
                     const std::string& email, const std::string& phone,
                     const std::string& department, const std::string& position,
                     double basicSalary, const std::string& password);

    bool updateEmployee(const std::string& employeeID);
    bool deleteEmployee(const std::string& employeeID);

    Employee* findByID(const std::string& employeeID)  const;
    Employee* findByEmail(const std::string& email)    const;

    Employee* authenticate(const std::string& employeeID, const std::string& password) const;

    void displayAllEmployees() const;
    void displayAllSalaries() const;
    void displayDetails(const Employee& emp) const;
    void displaySalaryInfo(const Employee& emp) const;
    void displayLeaveInfo(const Employee& emp) const;

    bool grantAdminAccess(const std::string& employeeID);
    bool revokeAdminAccess(const std::string& employeeID);

    std::string generateEmployeeID();
    int getTotalEmployees() const;
};

#endif
