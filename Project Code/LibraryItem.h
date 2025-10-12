#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H

#include <string>
#include <iostream>

class LibraryItem {
protected:
    int libraryID;
    double cost;
    std::string status;
    int loanPeriod;

public:
    virtual ~LibraryItem() = default; // Use default virtual destructor

    void SetLibraryID(int iD);
    void SetCost(double itemCost);
    void SetStatus(const std::string& newStatus);
    void SetLoanPeriod(int prd);

    int GetLibraryID() const;
    double GetCost() const;
    std::string GetStatus() const;
    int GetLoanPeriod() const;

    // Polymorphic behavior
    virtual std::string GetItemType() const = 0;
    virtual void InputDetails();
    virtual void EditDetails();
    virtual void PrintHeader(std::ostream& os) const = 0;
    virtual void PrintDetails(std::ostream& os) const = 0;
    virtual bool Matches(int criteria, const std::string& value) const;

    virtual std::string serialize() const = 0;
    virtual bool deserialize(std::istream& inFile) = 0;

    friend std::ostream& operator<<(std::ostream& os, const LibraryItem& item) {
        item.PrintDetails(os);
        return os;
    }
};

#endif