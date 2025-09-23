#include "Patron.h"

#include <sstream>
#include <iomanip>

Patron::Patron(){
    this-> patronName = "unknown";
    this-> patronID = 0000000;
    this-> fineBal = 0.00;
    this-> booksOut = 0;
}
void Patron::SetPatronName(string name){
    this-> patronName = name;
}
void Patron::SetPatronID(int id){//should be a 7-digit number
    string temp = to_string(id);
    if(temp.length() < 7 ){
        temp = string(7-temp.length(), '0') + temp;
    } else if(temp.length() > 7) {
        temp = temp.substr(0,7);
    }
    this-> patronID = stoi(temp);
}
void Patron::SetFineBalance(double bal){
    this-> fineBal = (bal * 100.0) / 100.0;
}
void Patron::SetBooksOut(int numBooksOut){
    if(this-> booksOut == 6){
        this-> booksOut = booksOut;
        cout << "Patron already has the maximum number of books checked out. " << endl;
        cout << "Cannot check out any more books." << endl;
    }
    else{
        this-> booksOut = numBooksOut;
    }
}
        
string Patron::GetPatronName() const{
    return patronName;
}
int Patron::GetPatronID() const{
    return patronID;
}
double Patron::GetFineBalance() const{
    return fineBal;
}
int Patron::GetBooksOut() const{
    return booksOut;
}

void Patron::IncreaseFineBalance(double amount) {
    fineBal += amount;  // Assuming fineBalance is a double variable in Patron class
}
void Patron::IncreaseBooksCheckedOut() {
    if (booksOut == 6) {
        cout << "Patron already has max number of books checked out. \n";
    }
    else{booksOut++; }
}
void Patron::DecreaseBooksCheckedOut() {
    if (booksOut > 0) {
        booksOut--;  // Assuming numBooksCheckedOut is an integer in Patron class
    }
    else{ cout << "Patron has no books checked out." << endl;}
}

void Patron::DisplayHeader() const {
    cout << left << setw(20) << "Patron ID"
    << setw(35) << "Patron Name" 
    << setw(20) << "Fine Balance"
    << setw(7) << "Number of Books Checked Out" << endl;

    cout << setfill('-') << setw(110) << "-" << endl;
    cout << setfill(' ');
}
void Patron::Display() const {
    cout << left << setw(20) << GetPatronID()
    << setw(35) << GetPatronName()
    << "$" << setw(19) << fixed << setprecision(2) << GetFineBalance()
    << setw(7) << GetBooksOut() << endl;
}

// Serialize patron data to a string for file storage
string Patron::serialize() const {
    stringstream ss;
    ss << patronName << "|" << patronID << "|" << fineBal << "|" << booksOut;
    return ss.str();
}

// Deserialize patron data from a file
bool Patron::deserialize(istream& inFile) {
    string line;
    if (getline(inFile, line)) {
        stringstream ss(line);

        getline(ss, patronName, '|');
        
        string tempPatronID, tempFineBal, tempBooksOut;
        getline(ss, tempPatronID, '|');
        getline(ss, tempFineBal, '|');
        getline(ss, tempBooksOut);

        // Convert extracted strings to appropriate types
        patronID = stoi(tempPatronID);
        fineBal = stod(tempFineBal);
        booksOut = stoi(tempBooksOut);

        return true;
    }
    return false;
}
