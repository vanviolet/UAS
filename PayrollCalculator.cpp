#include "PayrollCalculator.h"

long long PayrollCalculator::baseHonor() const { return BASE_HONOR; }

long long PayrollCalculator::overtimePay(double hoursWorked) const {
    const double overtimeHours = hoursWorked > BASE_HOURS ? hoursWorked - BASE_HOURS : 0.0;
    return static_cast<long long>(overtimeHours * OVERTIME_RATE);
}

long long PayrollCalculator::totalPay(double hoursWorked) const {
    return baseHonor() + overtimePay(hoursWorked);
}

long long PayrollCalculator::totalCompanyCost(const Employee* employees, std::size_t count) const {
    long long total = 0;
    for (std::size_t i = 0; i < count; ++i) {
        total += totalPay(employees[i].hoursWorked);
    }
    return total;
}
