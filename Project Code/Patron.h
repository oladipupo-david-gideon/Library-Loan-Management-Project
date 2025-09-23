#ifndef PATRONH
#define PATRONH

#include <string>
#include <iostream>
#include <cctype>
using namespace std;
    
class Patron{
    private:
        string patronName;
        int patronID;
        double fineBal;
        int booksOut;
        
    public:
        Patron();
        void SetPatronName(string name);
        void SetPatronID(int id);
        void SetFineBalance(double bal);
        void SetBooksOut(int numBooksOut);
        
        string GetPatronName() const;
        int GetPatronID() const;
        double GetFineBalance() const;
        int GetBooksOut() const;

        void DisplayHeader() const;
        void Display() const;

        void IncreaseFineBalance(double amount);
        void IncreaseBooksCheckedOut();
        void DecreaseBooksCheckedOut();

        string serialize() const;
        bool deserialize(istream& inFile);
};
    
#endif