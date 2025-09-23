#ifndef LOANSH
#define LOANSH

#include "Loan.h"
#include <vector>
#include <iostream>
#include <string>

class Loans{
    private:
        vector<Loan> loanList;

    public:
        int GenerateUniqueLoanID();

        vector<Loan>& GetLoanList();

        bool IsLoanOverdue(int loanID);
        bool IsPatronOverdue(int patronID);
        bool HasOtherLoansOverdue(int loanID);
        void updatePatronFineBalByClock(int loanID, vector<Patron>& patronL);

        void CheckOutItem(int patronID, int itemID, vector<Patron>& patronL, vector<LibraryItem*>& itemL);
        void CheckInItem(int loanID, vector<Patron>& patronL, vector<LibraryItem*>& itemL);
        void ReCheckItem(int loanID, vector<Patron>& patronL, vector<LibraryItem*>& itemL);
        void EditLoan(int loanID);
        void ReportLostItem(int loanID, vector<Patron>& patronL, vector<LibraryItem*>& itemL);
        
        void PrintAllLoans();
        void ListOverdueLoans();
        void AllLoansForPatron(int pID);
        void OverdueLoansForPatron(int pID);
        
        void UpdateLoanStatus(int loanID, vector<Patron>& patronL);
        void UpdateAllLoans(vector<Patron>& patronL);

        // File Operations
        void EnsureFileExists(const string& filename);
        void saveToFile() const;
        void loadFromFile();
};

#endif