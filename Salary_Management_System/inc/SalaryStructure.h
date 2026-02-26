#ifndef SALARYSTRUCTURE_H
#define SALARYSTRUCTURE_H

#include "Constants.h"

class Employee;

class SalaryStructure 
{
private:
    double basicSalary;
    double bonus;
    double deduction;
    double netSalary;
    int leavesTaken;

public:
    SalaryStructure();
    SalaryStructure(double basicSalary);

    double getBasicSalary() const;
    double getBonus() const;
    double getDeduction() const;
    double getNetSalary() const;
    int getLeavesTaken() const;

    void setBasicSalary(double amount);
    void setBonus(double amount);
    void setDeduction(double amount);
    void setNetSalary(double amount);
    void setLeavesTaken(int leaves);

    void compute();

    static double getDailyRate(double basicSalary);
    static int getLeaveBalance(int leavesTaken);
    static double computeBonus(double basicSalary, int leavesTaken);
    static double computeDeduction(double basicSalary, int leavesTaken);
    static double computeNetSalary(double basicSalary, int leavesTaken);

    void display() const;
};

#endif
