#ifndef PATRONSH
#define PATRONSH
    
#include "Patron.h"
#include <vector>

class Patrons{
    private:
        vector<Patron> patronList;
        
    public:
        vector<Patron>& GetPatronList();
        int GenerateUniquePatronID();
        void AddPatron();
        void EditPatron(int patronID);
        void DeletePatron(int patronID);
        void FindPatron();//based on criteria
        void PrintAllPatrons();
        void PrintPatron(int libraryID);
        void PrintPatronsWithFines();
        void PayFines(int patronID);
        
        void EnsureFileExists(const string& filename);
        void saveToFile();
        void loadFromFile();
};
    
#endif