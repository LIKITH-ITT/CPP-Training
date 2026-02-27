#include "Employee.h"
#include "Constants.h"

Employee::Employee(std::string& id, std::string& name,
                   std::string& dob, std::string& email,
                   std::string& phone, std::string& department, 
                   std::string& position,double basicSalary, std::string& password)
                    : employeeID(id), name(name), dob(dob), email(email),
                    phone(phone), department(department), position(position),
                    password(password), hasAdminAccess(false),
                    salary(basicSalary) {}

std::string Employee::getEmployeeID(){ return employeeID; }
std::string Employee::getName()      { return name; }
std::string Employee::getDob()       { return dob; }
std::string Employee::getEmail()     { return email; }
std::string Employee::getPhone()     { return phone; }
std::string Employee::getDepartment(){ return department; }
std::string Employee::getPosition()  { return position; }
std::string Employee::getPassword()  { return password; }
bool Employee::getHasAdminAccess()   { return hasAdminAccess; }
SalaryStructure Employee::getSalary(){ return salary; }
int Employee::getLeavesTaken()       { return salary.getLeavesTaken(); }
double Employee::getBasicSalary()    { return salary.getBasicSalary(); }

void Employee::setName(std::string& n)        { name = n; }
void Employee::setDob(std::string& d)         { dob = d; }
void Employee::setEmail(std::string& e)       { email = e; }
void Employee::setPhone(std::string& p)       { phone = p; }
void Employee::setDepartment(std::string& d)  { department = d; }
void Employee::setPosition(std::string& p)    { position = p; }
void Employee::setPassword(std::string& p)    { password = p; }
void Employee::setHasAdminAccess(bool access) { hasAdminAccess = access; }

void Employee::setBasicSalary(double amount) 
{
    salary.setBasicSalary(amount);
    salary.compute();
}

void Employee::setLeavesTaken(int leaves) 
{
    salary.setLeavesTaken(leaves);
    salary.compute();
}
