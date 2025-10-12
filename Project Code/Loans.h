#ifndef LOANS_H
#define LOANS_H

#include "Loan.h"
#include "Patrons.h"
#include "LibraryItems.h"
#include <vector>
#include <string>

class Loans {
private:
    std::vector<Loan> loanList;
    bool isDatePast(const Date& date) const;
    int GenerateUniqueLoanID();

public:
    void CheckOutItem(int patronID, int itemID, Patrons& patrons, LibraryItems& items);
    void CheckInItem(int loanID, Patrons& patrons, LibraryItems& items);
    
    void PrintAllLoans();
    void ListOverdueLoans();
    void AllLoansForPatron(int patronID);
    
    void UpdateAllLoanStatuses(Patrons& patrons);
    
    void saveToFile();
    void loadFromFile();
};

#endif