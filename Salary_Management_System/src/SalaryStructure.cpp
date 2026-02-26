#include "SalaryStructure.h"
#include "Constants.h"
#include "UIStrings.h"
#include <iostream>
#include <iomanip>

SalaryStructure::SalaryStructure() : basicSalary(0.0), bonus(0.0), deduction(0.0), netSalary(0.0), leavesTaken(0) {}

SalaryStructure::SalaryStructure(double basicSalary) : basicSalary(basicSalary), bonus(0.0), deduction(0.0), netSalary(basicSalary), leavesTaken(0) {}

double SalaryStructure::getBasicSalary() const { return basicSalary; }
double SalaryStructure::getBonus()        const { return bonus; }
double SalaryStructure::getDeduction()    const { return deduction; }
double SalaryStructure::getNetSalary()    const { return netSalary; }
int    SalaryStructure::getLeavesTaken()  const { return leavesTaken; }

void SalaryStructure::setBasicSalary(double amount)  { basicSalary = amount; }
void SalaryStructure::setBonus(double amount)         { bonus = amount; }
void SalaryStructure::setDeduction(double amount)     { deduction = amount; }
void SalaryStructure::setNetSalary(double amount)     { netSalary = amount; }
void SalaryStructure::setLeavesTaken(int leaves)      { leavesTaken = leaves; }

void SalaryStructure::compute() 
{
    bonus = computeBonus(basicSalary, leavesTaken);
    deduction = computeDeduction(basicSalary, leavesTaken);
    netSalary = computeNetSalary(basicSalary, leavesTaken);
}

double SalaryStructure::getDailyRate(double basicSalary) 
{
    return basicSalary / WORKING_DAYS;
}

int SalaryStructure::getLeaveBalance(int leavesTaken) 
{
    int leaveBalance = 0;
    if(ALLOCATED_LEAVES > leavesTaken)
        leaveBalance = ALLOCATED_LEAVES - leavesTaken;
    return leaveBalance;
}

double SalaryStructure::computeBonus(double basicSalary, int leavesTaken) 
{
    double bonus = 0.0;
    if (leavesTaken < ALLOCATED_LEAVES)
        bonus = (ALLOCATED_LEAVES - leavesTaken) * getDailyRate(basicSalary);
    return bonus;
}

double SalaryStructure::computeDeduction(double basicSalary, int leavesTaken) 
{
    double deduction = 0.0;
    if (leavesTaken > ALLOCATED_LEAVES)
        deduction = (leavesTaken - ALLOCATED_LEAVES) * getDailyRate(basicSalary);
    return deduction;
}

double SalaryStructure::computeNetSalary(double basicSalary, int leavesTaken) 
{
    return basicSalary + computeBonus(basicSalary, leavesTaken) - computeDeduction(basicSalary, leavesTaken);
}

void SalaryStructure::display() const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << UIStrings::SALARY_HEADER;
    std::cout << UIStrings::LABEL_BASIC_SAL << basicSalary << "\n";
    std::cout << UIStrings::LABEL_LEAVES_TAKEN << leavesTaken << "\n";
    std::cout << UIStrings::LABEL_ALLOC_LVS << ALLOCATED_LEAVES << "\n";
    std::cout << UIStrings::LABEL_LEAVE_BAL2 << getLeaveBalance(leavesTaken) << "\n";
    std::cout << UIStrings::LABEL_DAILY_RATE << getDailyRate(basicSalary) << "\n";
    if (bonus > 0.0)
        std::cout << UIStrings::LABEL_BONUS << bonus << "\n";
    if (deduction > 0.0)
        std::cout << UIStrings::LABEL_DEDUCTION << deduction << "\n";
    std::cout << UIStrings::LABEL_NET_SAL << netSalary << "\n";
    std::cout << UIStrings::SALARY_FOOTER;
}
