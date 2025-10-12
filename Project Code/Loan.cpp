#include "Loan.h"
#include "LibraryClock.h"
#include <sstream>
#include <cstdio> // for sscanf

Loan::Loan() {
    loanID = 0;
    itemID = 0;
    patronID = 0;
    loanStatus = "Normal";
    numRechecks = 0;
}

void Loan::SetLoanID(int id) { loanID = id; }
void Loan::SetItemID(int id) { itemID = id; }
void Loan::SetPatronID(int id) { patronID = id; }
void Loan::SetLoanStatus(const std::string& status) { loanStatus = status; }
void Loan::SetNumRechecks(int num) { numRechecks = num; }

int Loan::GetLoanID() const { return loanID; }
int Loan::GetItemID() const { return itemID; }
int Loan::GetPatronID() const { return patronID; }
int Loan::GetNumRechecks() const { return numRechecks; }
Date Loan::GetDueDate() const { return dueDate; }
std::string Loan::GetLoanStatus() const { return loanStatus; }

void Loan::SetDueDate(int loanDays) {
    std::string currentDate = LibraryClock::getCurrentDate();
    int currentMonth, currentDay, currentYear;
    sscanf(currentDate.c_str(), "%d/%d/%d", &currentMonth, &currentDay, &currentYear);

    tm dueDateTm = {};
    dueDateTm.tm_mday = currentDay + loanDays;
    dueDateTm.tm_mon = currentMonth - 1;
    dueDateTm.tm_year = currentYear - 1900;

    mktime(&dueDateTm); // Normalize the date

    dueDate.day = dueDateTm.tm_mday;
    dueDate.month = dueDateTm.tm_mon + 1;
    dueDate.year = dueDateTm.tm_year + 1900;
}

std::string Loan::GetDueDateAsString() const {
    std::stringstream ss;
    ss << dueDate.month << "/" << dueDate.day << "/" << dueDate.year;
    return ss.str();
}

std::string Loan::serialize() const {
    std::stringstream ss;
    ss << loanID << "|" << itemID << "|" << patronID << "|"
       << dueDate.month << "|" << dueDate.day << "|" << dueDate.year << "|"
       << loanStatus << "|" << numRechecks;
    return ss.str();
}

bool Loan::deserialize(std::istream& inFile) {
    std::string line;
    if (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string tempLoanID, tempItemID, tempPatronID, tempMonth, tempDay, tempYear, tempRechecks;
        
        std::getline(ss, tempLoanID, '|');
        std::getline(ss, tempItemID, '|');
        std::getline(ss, tempPatronID, '|');
        std::getline(ss, tempMonth, '|');
        std::getline(ss, tempDay, '|');
        std::getline(ss, tempYear, '|');
        std::getline(ss, loanStatus, '|');
        std::getline(ss, tempRechecks);

        try {
            loanID = std::stoi(tempLoanID);
            itemID = std::stoi(tempItemID);
            patronID = std::stoi(tempPatronID);
            dueDate.month = std::stoi(tempMonth);
            dueDate.day = std::stoi(tempDay);
            dueDate.year = std::stoi(tempYear);
            numRechecks = std::stoi(tempRechecks);
        } catch(const std::exception&) {
            return false;
        }
        return true;
    }
    return false;
}