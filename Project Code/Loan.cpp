#include "Loan.h"
#include "LibraryClock.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

Loan::Loan(){
    this->itemID = 0;
    this->patronID = 0;
    this->loanID = 0;
    this->loanStatus = "normal";
    this->dueDate = {0, 0, 0};
    this->numOfRechecks = 0;
    this->previousOverdueDays = 0;
}
void Loan::SetItemID(int itemID){
    this->itemID = itemID;
}
void Loan::SetPatronID(int patronID){
    this->patronID = patronID;
}
void Loan::SetLoanID(int loanID){
    this->loanID = loanID;
}
void Loan::SetNumRechecks(int numRe){
    this->numOfRechecks = numRe;
}
void Loan::SetLoanStatus(string loanStat){
    this->loanStatus = loanStat;
}
void Loan::SetDueDate() {
    string currentDate = LibraryClock::getCurrentDate(); // Expected format: "mm/dd/yyyy"
    int day, month, year;
    char slash1, slash2; // To read '/' separators

    stringstream ss(currentDate);
    ss >> month >> slash1 >> day >> slash2 >> year; // Extract correctly as "mm/dd/yyyy"

    if (ss.fail() || slash1 != '/' || slash2 != '/') {
        cerr << "Error: Invalid date format from LibraryClock!" << endl;
        return;
    }

    // Convert to tm structure
    tm dueDateTm = {};
    dueDateTm.tm_mday = day + 10; // Add 10 days
    dueDateTm.tm_mon = month - 1; // tm_mon is 0-based
    dueDateTm.tm_year = year - 1900; // Convert full year to tm_year format

    // Normalize date (handles overflow, e.g., moving to next month/year)
    mktime(&dueDateTm);

    // Store in dueDate structure
    dueDate.day = dueDateTm.tm_mday;
    dueDate.month = dueDateTm.tm_mon + 1; // Convert back to 1-based month
    dueDate.year = dueDateTm.tm_year + 1900; // Convert back to full year
}
void Loan::SetPreviousOverdueDays(int days) { 
    previousOverdueDays = days; 
}


int Loan::GetLoanID() const{
    return loanID;
}
int Loan::GetItemID() const{
    return itemID;
}
int Loan::GetPatronID() const{
    return patronID;
}
int Loan::GetNumRechecks() const{
    return numOfRechecks;
}
string Loan::GetDueDate() const{
    stringstream ss;
    ss << dueDate.month << "/" << dueDate.day << "/" << dueDate.year;
    return ss.str();
}
string Loan::GetLoanStatus() const{
    return loanStatus;
}
int Loan::GetPreviousOverdueDays() const { 
    return previousOverdueDays; 
}

// Serialization
string Loan::serialize() const {
    stringstream ss;
    ss << loanID << "|" << itemID << "|" << patronID << "|"
       << dueDate.month << "|" << dueDate.day << "|" << dueDate.year << "|"
       << loanStatus;
    return ss.str();
}

//Deserialization
bool Loan::deserialize(istream& inFile) {
    string line;
    if (getline(inFile, line)) {
        stringstream ss(line);

        string tempLoanID, tempItemID, tempPatronID, tempMonth, tempDay, tempYear;

        // Extract values as strings
        getline(ss, tempLoanID, '|');
        getline(ss, tempItemID, '|');
        getline(ss, tempPatronID, '|');
        getline(ss, tempMonth, '|');
        getline(ss, tempDay, '|');
        getline(ss, tempYear, '|');
        getline(ss, loanStatus); // Loan status is the last field

        // Convert extracted strings to appropriate types
        loanID = stoi(tempLoanID);
        itemID = stoi(tempItemID);
        patronID = stoi(tempPatronID);
        dueDate.month = stoi(tempMonth);
        dueDate.day = stoi(tempDay);
        dueDate.year = stoi(tempYear);

        return true;
    }
    return false; // File read error
}