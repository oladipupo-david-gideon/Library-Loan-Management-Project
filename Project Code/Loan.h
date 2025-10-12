#ifndef LOAN_H
#define LOAN_H

#include <string>
#include <iostream>

struct Date {
    int month = 0, day = 0, year = 0;
};

class Loan {
private:
    int loanID;
    int itemID;
    int patronID;
    std::string loanStatus;
    Date dueDate;
    int numRechecks;

public:
    Loan();
    void SetLoanID(int id);
    void SetItemID(int id);
    void SetPatronID(int id);
    void SetLoanStatus(const std::string& status);
    void SetDueDate(int loanDays); // Accepts the specific item's loan period
    void SetNumRechecks(int num);

    int GetLoanID() const;
    int GetItemID() const;
    int GetPatronID() const;
    int GetNumRechecks() const;
    Date GetDueDate() const;
    std::string GetDueDateAsString() const;
    std::string GetLoanStatus() const;

    std::string serialize() const;
    bool deserialize(std::istream& inFile);
};

#endif