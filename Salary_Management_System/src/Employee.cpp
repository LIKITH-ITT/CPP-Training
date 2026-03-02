#include "Employee.h"
#include "Constants.h"

Employee::Employee(const std::string& id, const  std::string& name,
                   const std::string& dob, const  std::string& email, 
                   const std::string& phone, const std::string& department, 
                   const std::string& position, const double basicSalary, 
                   const std::string& password)
: employeeID(id), name(name), dob(dob), email(email),phone(phone), department(department), position(position),password(password), hasAdminAccess(false),salary(basicSalary) {}

std::string Employee::getEmployeeID() const
{
    return employeeID; 
}
std::string Employee::getName() const     
{
    return name; 
}
std::string Employee::getDob() const       
{
    return dob;
}
std::string Employee::getEmail() const     
{
    return email; 
}
std::string Employee::getPhone() const    
{
    return phone; 
}
std::string Employee::getDepartment() const
{
    return department; 
}
std::string Employee::getPosition() const 
{
    return position; 
}
std::string Employee::getPassword() const
{
    return password; 
}
bool Employee::getHasAdminAccess() const  
{
    return hasAdminAccess; 
}
SalaryStructure Employee::getSalary() const
{
    return salary; 
}
int Employee::getLeavesTaken() const     
{
    return salary.getLeavesTaken(); 
}
double Employee::getBasicSalary() const  
{
    return salary.getBasicSalary(); 
}

void Employee::setName(const std::string& n)        
{ 
    name = n; 
}
void Employee::setDob(const std::string& d)         
{ 
    dob = d; 
}
void Employee::setEmail(const std::string& e)       
{ 
    email = e; 
}
void Employee::setPhone(const std::string& p)       
{ 
    phone = p; 
}
void Employee::setDepartment(const std::string& d)  
{ 
    department = d; 
}
void Employee::setPosition(const std::string& p)    
{ 
    position = p; 
}
void Employee::setPassword(const std::string& p)    
{ 
    password = p; 
}
void Employee::setHasAdminAccess(const bool access) 
{ 
    hasAdminAccess = access; 
}

void Employee::setBasicSalary(const double amount) 
{
    salary.setBasicSalary(amount);
    salary.compute();
}

void Employee::setLeavesTaken(const int leaves) 
{
    salary.setLeavesTaken(leaves);
    salary.compute();
}
