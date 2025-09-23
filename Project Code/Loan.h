#ifndef LOANH
#define LOANH

#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class Loan{
    private:
        int itemID;
        int patronID;
        int loanID;
        string loanStatus;
        struct {
            int month, day, year;
        } dueDate;
        int numOfRechecks;
        int previousOverdueDays;

    public:
        Loan();
        void SetLoanID(int loanID);
        void SetItemID(int bookID);
        void SetPatronID(int patronID);
        void SetLoanStatus(string loanStat);
        void SetDueDate();
        void SetNumRechecks(int numRe);
        void SetPreviousOverdueDays(int days);

        int GetLoanID() const;
        int GetItemID() const;
        int GetPatronID() const;
        int GetNumRechecks() const;
        string GetDueDate() const;
        string GetLoanStatus() const;
        int GetPreviousOverdueDays() const;


        string serialize() const;
        bool deserialize(istream& inFile);
};

#endif