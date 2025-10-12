#ifndef PATRON_H
#define PATRON_H

#include <string>
#include <iostream>

class Patron {
private:
    std::string patronName;
    int patronID;
    double fineBal;
    int itemsOut;

public:
    Patron();

    void SetPatronName(const std::string& name);
    void SetPatronID(int id);
    void SetFineBalance(double bal);
    void SetItemsOut(int numItemsOut);
    
    std::string GetPatronName() const;
    int GetPatronID() const;
    double GetFineBalance() const;
    int GetItemsOut() const;

    void AdjustFineBalance(double amount);
    void IncrementItemsOut();
    void DecrementItemsOut();

    std::string serialize() const;
    bool deserialize(std::istream& inFile);
};
    
#endif