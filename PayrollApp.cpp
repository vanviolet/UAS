#include "PayrollApp.h"

#include "Employee.h"
#include "PayrollCalculator.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

namespace {

double requestPositiveHours(std::size_t index) {
    double hours = 0.0;
    while (true) {
        std::cout << "  Jam kerja pegawai ke-" << index + 1 << " (jam): ";
        if (std::cin >> hours && hours >= 0.0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return hours;
        }
        std::cout << "  Input tidak valid. Masukkan angka jam kerja yang benar.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void collectEmployees(Employee* employees, std::size_t count) {
    for (std::size_t i = 0; i < count; ++i) {
        std::cout << "\nData pegawai ke-" << i + 1 << '\n';
        std::cout << "  Nama: ";
        std::getline(std::cin, employees[i].name);
        while (employees[i].name.empty()) {
            std::cout << "  Nama tidak boleh kosong. Masukkan ulang: ";
            std::getline(std::cin, employees[i].name);
        }
        employees[i].hoursWorked = requestPositiveHours(i);
    }
}

void printPayroll(const Employee* employees,
                  std::size_t count,
                  const PayrollCalculator& calculator,
                  const std::string& companyName,
                  const std::string& reportDate) {
    if (count == 0) {
        std::cout << "Belum ada data pegawai. Gunakan fitur 1 terlebih dahulu.\n";
        return;
    }

    std::cout << "\n" << companyName << '\n';
    std::cout << "Tanggal : " << reportDate << "\n";
    std::cout << std::string(60, '=') << "\n";
    std::cout << std::left
              << std::setw(4) << "No."
              << std::setw(15) << "Nama"
              << std::setw(12) << "Honor"
              << std::setw(12) << "Jam Kerja"
              << std::setw(15) << "Honor Lembur"
              << "Total" << '\n';
    std::cout << std::string(60, '=') << "\n";

    for (std::size_t i = 0; i < count; ++i) {
        const long long base = calculator.baseHonor();
        const long long overtime = calculator.overtimePay(employees[i].hoursWorked);
        const long long total = calculator.totalPay(employees[i].hoursWorked);

        std::cout << std::left
                  << std::setw(4) << i + 1
                  << std::setw(15) << employees[i].name
                  << std::setw(12) << base
                  << std::setw(12) << employees[i].hoursWorked
                  << std::setw(15) << overtime
                  << total << '\n';
    }

    std::cout << std::string(60, '=') << "\n";
    std::cout << "Total Honor Pegawai Sebesar : Rp "
              << calculator.totalCompanyCost(employees, count) << "\n\n";
}

} // namespace

void runPayrollApp() {
    PayrollCalculator calculator;
    Employee* employees = nullptr;
    std::size_t employeeCount = 0;
    std::string companyName = "PT. Mering Gembira";
    std::string reportDate = "12 Januari 2026";

    bool running = true;
    while (running) {
        std::cout << "==============================\n";
        std::cout << " Menu Utama\n";
        std::cout << "==============================\n";
        std::cout << "1. Input/ubah data pegawai\n";
        std::cout << "2. Tampilkan laporan honor\n";
        std::cout << "0. Keluar\n";
        std::cout << "Pilih fitur: ";

        int choice = -1;
        if (!(std::cin >> choice)) {
            std::cout << "Input tidak dikenal. Silakan ulangi.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            std::size_t count = 0;
            std::cout << "Masukkan jumlah pegawai: ";
            while (!(std::cin >> count) || count == 0) {
                std::cout << "Jumlah pegawai minimal 1. Masukkan ulang: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            delete[] employees;
            employees = new Employee[count];
            employeeCount = count;

            collectEmployees(employees, employeeCount);

            std::cout << "\nNama instansi (default: " << companyName << "): ";
            std::string newCompany;
            std::getline(std::cin, newCompany);
            if (!newCompany.empty()) {
                companyName = newCompany;
            }

            std::cout << "Tanggal laporan (default: " << reportDate << "): ";
            std::string newDate;
            std::getline(std::cin, newDate);
            if (!newDate.empty()) {
                reportDate = newDate;
            }

            std::cout << "Data berhasil disimpan. Gunakan fitur 2 untuk melihat laporan.\n\n";
            break;
        }
        case 2:
            printPayroll(employees, employeeCount, calculator, companyName, reportDate);
            break;
        case 0:
            running = false;
            break;
        default:
            std::cout << "Pilihan tidak tersedia.\n";
            break;
        }
    }

    delete[] employees;
    std::cout << "Program selesai.\n";
}
