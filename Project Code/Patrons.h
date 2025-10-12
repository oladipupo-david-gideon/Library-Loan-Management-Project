#ifndef PATRONS_H
#define PATRONS_H
    
#include "Patron.h"
#include <vector>
#include <string>

class Patrons {
private:
    std::vector<Patron> patronList;
    
public:
    std::vector<Patron>& GetPatronList();
    int GenerateUniquePatronID();
    void AddPatron();
    void EditPatron(int patronID);
    void DeletePatron(int patronID);
    void FindPatron();
    void PrintAllPatrons();
    void PrintPatron(int patronID);
    void PrintPatronsWithFines();
    void PayFines(int patronID);
    
    void saveToFile();
    void loadFromFile();
};
    
#endif