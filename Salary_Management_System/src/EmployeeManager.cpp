#include "EmployeeManager.h"
#include "Logger.h"
#include "InputValidator.h"
#include "UIStrings.h"
#include "SalaryPrinter.h"
#include <iostream>
#include <iomanip>
#include <sstream>

EmployeeManager::EmployeeManager()
    : size(0), capacity(INITIAL_CAPACITY), nextEmployeeID(INITIAL_EMP_ID) 
{
    employees = new Employee*[capacity];
}

EmployeeManager::~EmployeeManager() 
{
    for (int i = 0; i < size; i++)
        delete employees[i];
    delete[] employees;
}

void EmployeeManager::resize() 
{
    int newCapacity = capacity * 2;
    Employee** newArr = new Employee*[newCapacity];

    for (int i = 0; i < size; i++)
        newArr[i] = employees[i];
    delete[] employees;
    employees = newArr;
    capacity  = newCapacity;
}

void EmployeeManager::shrink() 
{
    if (capacity <= INITIAL_CAPACITY) 
        return;
    int newCapacity = capacity / 2;
    Employee** newArr = new Employee*[newCapacity];
    for (int i = 0; i < size; i++) 
        newArr[i] = employees[i];
    delete[] employees;
    employees = newArr;
    capacity  = newCapacity;
}

bool EmployeeManager::addEmployee(std::string& name, std::string& dob,
                                   std::string& email, std::string& phone,
                                   std::string& department, std::string& position,
                                   double basicSalary, std::string& password) 
{
    if (findByEmail(email) != nullptr) 
    {
        Logger::warning("Add failed: email already exists - " + email);
        return false;
    }
    if (size == capacity) resize();

    std::string id  = generateEmployeeID();
    employees[size] = new Employee(id, name, dob, email, phone, department, position, basicSalary, password);
    size++;
    Logger::info("Employee added: " + id + " - " + name);
    return true;
}

bool EmployeeManager::updateEmployee(std::string& employeeID) 
{
    Employee* emp = findByID(employeeID);
    if (!emp) 
    {
        Logger::warning("Update failed: employee not found - " + employeeID);
        return false;
    }

    std::cout << UIStrings::UPDATE_BLANK_ENTER;

    std::string input;

    std::cout << "  Name [" << emp->getName() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) 
    {
        if (InputValidator::isValidName(input)) emp->setName(input);
        else std::cout << UIStrings::UPDATE_INVALID_NAME;
    }

    std::cout << "  DOB (DD/MM/YYYY) [" << emp->getDob() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) 
    {
        if (InputValidator::isValidDate(input)) emp->setDob(input);
        else std::cout << UIStrings::UPDATE_INVALID_DATE;
    }

    std::cout << "  Email [" << emp->getEmail() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) 
    {
        if (InputValidator::isValidEmail(input)) emp->setEmail(input);
        else std::cout << UIStrings::UPDATE_INVALID_EMAIL;
    }

    std::cout << "  Phone [" << emp->getPhone() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) 
    {
        if (InputValidator::isValidPhone(input)) emp->setPhone(input);
        else std::cout << UIStrings::UPDATE_INVALID_PHONE;
    }

    std::cout << "  Department [" << emp->getDepartment() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) 
        emp->setDepartment(input);

    std::cout << "  Position [" << emp->getPosition() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) 
        emp->setPosition(input);

    std::cout << "  Basic Salary [" << emp->getBasicSalary() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) 
    {
            double sal = std::stod(input);
            if (InputValidator::isPositiveDouble(sal)) 
                emp->setBasicSalary(sal);
            else 
                std::cout << UIStrings::UPDATE_INVALID_SAL;
    }

    Logger::info("Employee updated: " + employeeID);
    return true;
}

bool EmployeeManager::deleteEmployee(std::string& employeeID) 
{
    for (int i = 0; i < size; i++) 
    {
        if (employees[i]->getEmployeeID() == employeeID) 
        {
            delete employees[i];
            for (int j = i; j < size - 1; j++) employees[j] = employees[j + 1];
            size--;
            Logger::info("Employee deleted: " + employeeID);
            if (size < capacity / 2) shrink();
            return true;
        }
    }
    Logger::warning("Delete failed: employee not found - " + employeeID);
    return false;
}

Employee* EmployeeManager::findByID(std::string& employeeID) 
{
    for (int i = 0; i < size; i++)
        if (employees[i]->getEmployeeID() == employeeID) return employees[i];
    return nullptr;
}

Employee* EmployeeManager::findByEmail(std::string& email) 
{
    for (int i = 0; i < size; i++)
        if (employees[i]->getEmail() == email) return employees[i];
    return nullptr;
}

Employee* EmployeeManager::authenticate(std::string& employeeID, std::string& password) 
{
    Employee* emp = findByID(employeeID);
    if (emp && emp->getPassword() == password) 
        return emp;
    return nullptr;
}

void EmployeeManager::displayAllEmployees() 
{
    if (size == 0) 
    {
        std::cout << UIStrings::ERR_NO_EMPLOYEES;
        return;
    }
    std::cout << "\n  " << std::left
              << std::setw(10) << UIStrings::COL_ID
              << std::setw(20) << UIStrings::COL_NAME
              << std::setw(15) << UIStrings::COL_DEPT
              << std::setw(15) << UIStrings::COL_POSITION
              << std::setw(10) << UIStrings::COL_ADMIN
              << "\n";
    std::cout << "  " << std::string(70, '-') << "\n";
    for (int i = 0; i < size; i++) 
    {
        std::cout << "  " << std::left
                  << std::setw(10) << employees[i]->getEmployeeID()
                  << std::setw(20) << employees[i]->getName()
                  << std::setw(15) << employees[i]->getDepartment()
                  << std::setw(15) << employees[i]->getPosition()
                  << std::setw(10) << (employees[i]->getHasAdminAccess() ? UIStrings::YES : UIStrings::NO)
                  << "\n";
    }
}

void EmployeeManager::displayAllSalaries() 
{
    if (size == 0) 
    {
        std::cout << UIStrings::ERR_NO_EMPLOYEES;
        return;
    }
    std::cout << "\n  " << std::left
              << std::setw(10) << UIStrings::COL_ID
              << std::setw(20) << UIStrings::COL_NAME
              << std::setw(12) << UIStrings::COL_BASIC
              << std::setw(8)  << UIStrings::COL_LEAVES
              << std::setw(10) << UIStrings::COL_BONUS
              << std::setw(12) << UIStrings::COL_DEDUCTION
              << std::setw(12) << UIStrings::COL_NET
              << "\n";
    std::cout << "  " << std::string(84, '-') << "\n";
    std::cout << std::fixed << std::setprecision(2);
    for (int i = 0; i < size; i++) 
    {
        double basic  = employees[i]->getBasicSalary();
        int leaves = employees[i]->getLeavesTaken();
        std::cout << "  " << std::left
                  << std::setw(10) << employees[i]->getEmployeeID()
                  << std::setw(20) << employees[i]->getName()
                  << std::setw(12) << basic
                  << std::setw(8)  << leaves
                  << std::setw(10) << SalaryStructure::computeBonus(basic, leaves)
                  << std::setw(12) << SalaryStructure::computeDeduction(basic, leaves)
                  << std::setw(12) << SalaryStructure::computeNetSalary(basic, leaves)
                  << "\n";
    }
}

void EmployeeManager::displayDetails(Employee& emp)
{
    std::cout << UIStrings::DETAIL_HEADER;
    std::cout << UIStrings::LABEL_ID << emp.getEmployeeID() << "\n";
    std::cout << UIStrings::LABEL_NAME << emp.getName() << "\n";
    std::cout << UIStrings::LABEL_DOB << emp.getDob() << "\n";
    std::cout << UIStrings::LABEL_EMAIL << emp.getEmail() << "\n";
    std::cout << UIStrings::LABEL_PHONE << emp.getPhone() << "\n";
    std::cout << UIStrings::LABEL_DEPT << emp.getDepartment() << "\n";
    std::cout << UIStrings::LABEL_POSITION << emp.getPosition() << "\n";
    std::cout << UIStrings::LABEL_ADMIN << (emp.getHasAdminAccess() ? UIStrings::YES : UIStrings::NO) << "\n";
    std::cout << UIStrings::DETAIL_FOOTER;
}

void EmployeeManager::displayLeaveInfo(Employee& emp)
{
    std::cout << UIStrings::LEAVE_HEADER;
    std::cout << UIStrings::LABEL_ALLOC_LEAVES << ALLOCATED_LEAVES << "\n";
    std::cout << UIStrings::LABEL_TAKEN_LEAVES << emp.getLeavesTaken() << "\n";
    std::cout << UIStrings::LABEL_LEAVE_BAL << SalaryStructure::getLeaveBalance(emp.getLeavesTaken()) << "\n";
    std::cout << UIStrings::LEAVE_FOOTER;
}

void EmployeeManager::displaySalaryInfo(Employee& emp) 
{
    SalaryStructure salary = emp.getSalary();
    salary.compute();
    SalaryPrinter::display(salary);
}

bool EmployeeManager::grantAdminAccess(std::string& employeeID) 
{
    Employee* emp = findByID(employeeID);
    if (!emp) return false;
    emp->setHasAdminAccess(true);
    return true;
}

bool EmployeeManager::revokeAdminAccess(std::string& employeeID) 
{
    Employee* emp = findByID(employeeID);
    if (!emp) return false;
    emp->setHasAdminAccess(false);
    Logger::info("Admin access revoked from: " + employeeID);
    return true;
}

std::string EmployeeManager::generateEmployeeID() 
{
    std::ostringstream oss;
    oss << "EMP" << nextEmployeeID++;
    return oss.str();
}

int EmployeeManager::getTotalEmployees() 
{
    return size;
}
