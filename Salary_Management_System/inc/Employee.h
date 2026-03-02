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
    Employee(const std::string& id, const std::string& name,
             const std::string& dob, const std::string& email,
             const std::string& phone, const std::string& department,
             const std::string& position, const double basicSalary,
             const std::string& password);

    std::string getEmployeeID() const;
    std::string getName() const;
    std::string getDob() const;
    std::string getEmail() const;
    std::string getPhone() const;
    std::string getDepartment() const;
    std::string getPosition() const;
    std::string getPassword() const;
    bool getHasAdminAccess() const;
    SalaryStructure getSalary() const;
    int getLeavesTaken() const;
    double getBasicSalary() const;

    void setName(const std::string& name);
    void setDob(const std::string& dob);
    void setEmail(const std::string& email);
    void setPhone(const std::string& phone);
    void setDepartment(const std::string& department);
    void setPosition(const std::string& position);
    void setPassword(const std::string& password);
    void setHasAdminAccess(bool access);
    void setBasicSalary(double amount);
    void setLeavesTaken(int leaves);

};

#endif
