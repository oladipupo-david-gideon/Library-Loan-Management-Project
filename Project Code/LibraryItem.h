#ifndef LIBRARYITEM
#define LIBRARYITEM

#include <string>
#include <iostream>
using namespace std;

class LibraryItem {
protected:
    int libraryID;
    double cost;
    string status;
    int loanPeriod;

public:
    virtual ~LibraryItem() {}

    void SetLibraryID(int iD);
    void SetCost(double cost);
    void SetStatus(const string& status);
    void SetLoanPeriod(int prd);

    int GetLibraryID() const;
    double GetCost() const;
    string GetStatus() const;
    int GetLoanPeriod() const;

    // Polymorphic behavior
    virtual string GetItemType() const = 0;
    virtual void InputDetails() = 0;
    virtual void EditDetails() = 0;
    virtual void PrintHeader(ostream& os) const = 0;
    virtual void PrintDetails(ostream& os) const = 0;
    virtual bool Matches(int criteria, const string& value) const = 0;

    virtual string serialize() const = 0;
    virtual bool deserialize(istream& inFile) = 0;

    friend ostream& operator<<(ostream& os, const LibraryItem& item) {
        item.PrintDetails(os);
        return os;
    }
};
    
#endif