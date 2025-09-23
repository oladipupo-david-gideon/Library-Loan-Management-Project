#include "LibraryItem.h"

#include <iostream>
#include <sstream>

using namespace std;

void LibraryItem::SetLibraryID(int iD){
    string temp = to_string(iD);
    if(temp.length() < 6){
        temp = string(6 - temp.length(), '0') + temp;
    } else if(temp.length() > 6) {
        cerr << "Error: Library ID exceeds 6 digits. Truncating." << endl;
        temp = temp.substr(0, 6);  // Truncate to 6 digits
    }
    this->libraryID = stoi(temp);
}

void LibraryItem::SetCost(double cost){
    this->cost = double(cost * 100.0) / 100.0;
}

void LibraryItem::SetStatus(const string& stat){
    this->status = stat;
}

void LibraryItem::SetLoanPeriod(int prd){
    this->loanPeriod = prd;
}

int LibraryItem::GetLibraryID() const{
    return libraryID;
}

double LibraryItem::GetCost() const{
    return cost;
}

string LibraryItem::GetStatus() const{
    return status;
}

int LibraryItem::GetLoanPeriod() const{
    return loanPeriod;
}
