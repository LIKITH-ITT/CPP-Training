#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include "SalaryStructure.h"

class Employee {
private:
    std::string employeeID;
    std::string name;
    std::string dob;
    std::string email;
    std::string phone;
    std::string department;
    std::string position;
    std::string password;
    bool hasAdminAccess;
    SalaryStructure salary; 
    
public:
    Employee( std::string& id,  std::string& name,
              std::string& dob,  std::string& email,
              std::string& phone,  std::string& department,
              std::string& position, double basicSalary,
              std::string& password);

    std::string getEmployeeID();
    std::string getName();
    std::string getDob();
    std::string getEmail();
    std::string getPhone();
    std::string getDepartment() ;
    std::string getPosition();
    std::string getPassword();
    bool getHasAdminAccess();
    SalaryStructure getSalary();
    int getLeavesTaken();
    double getBasicSalary();

    void setName( std::string& name);
    void setDob( std::string& dob);
    void setEmail( std::string& email);
    void setPhone( std::string& phone);
    void setDepartment( std::string& department);
    void setPosition( std::string& position);
    void setPassword( std::string& password);
    void setHasAdminAccess(bool access);
    void setBasicSalary(double amount);
    void setLeavesTaken(int leaves);

};

#endif
