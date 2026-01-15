#ifndef PAYROLL_CALCULATOR_H
#define PAYROLL_CALCULATOR_H

#include "Employee.h"
#include <cstddef>

class PayrollCalculator {
public:
    long long baseHonor() const;
    long long overtimePay(double hoursWorked) const;
    long long totalPay(double hoursWorked) const;
    long long totalCompanyCost(const Employee* employees, std::size_t count) const;

private:
    static constexpr long long BASE_HONOR = 25000;
    static constexpr long long OVERTIME_RATE = 1500;
    static constexpr double BASE_HOURS = 8.0;
};

#endif // PAYROLL_CALCULATOR_H
