#ifndef SALARYPRINTER_H
#define SALARYPRINTER_H

#include <iostream>
#include <iomanip>
#include <string>
#include "UIStrings.h"
#include "SalaryStructure.h"

namespace SalaryPrinter
{
    inline void display(SalaryStructure& salary) 
    {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << UIStrings::SALARY_HEADER;
        std::cout << UIStrings::LABEL_BASIC_SAL << salary.getBasicSalary() << "\n";
        std::cout << UIStrings::LABEL_LEAVES_TAKEN << salary.getLeavesTaken() << "\n";
        std::cout << UIStrings::LABEL_ALLOC_LVS << ALLOCATED_LEAVES << "\n";
        std::cout << UIStrings::LABEL_LEAVE_BAL2 << salary.getLeaveBalance(salary.getLeavesTaken()) << "\n";
        std::cout << UIStrings::LABEL_DAILY_RATE << salary.getDailyRate(salary.getBasicSalary()) << "\n";
        if (salary.getBonus() > 0.0)
            std::cout << UIStrings::LABEL_BONUS << salary.getBonus() << "\n";
        if (salary.getDeduction() > 0.0)
            std::cout << UIStrings::LABEL_DEDUCTION << salary.getDeduction() << "\n";
        std::cout << UIStrings::LABEL_NET_SAL << salary.getNetSalary() << "\n";
        std::cout << UIStrings::SALARY_FOOTER;
    }
}

#endif
