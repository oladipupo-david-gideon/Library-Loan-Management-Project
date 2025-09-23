#include "Book.h"

#include <iostream>
#include <sstream>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <array>
#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include <vector>
#include <regex>
#include <iomanip>

using namespace std;

Book::Book(){
    this-> authorName = "unknown";
    this-> bookTitle = "unknown";
    this-> isbn = 0000000000;
    this-> libraryID = 000000;
    this-> cost = 0.00;
    this-> status = "none";
    this-> category = "unknown";
}


void Book::SetAuthorName(const string& name) {
    this->authorName = name;
}

void Book::SetBookTitle(const string& title) {
    this->bookTitle = title;
}
void Book::SetISBN(long isbn_num){//should be a 10-digit number
    string temp = to_string(isbn_num);
    if(temp.length() < 10 ){
        temp = string(10-temp.length(), '0') + temp;
    } else if(temp.length() > 10) {
        temp = temp.substr(0,10);
    }
    this-> isbn = stol(temp);
}
void Book::SetBookCategory(const string& cat) {
    this->category = cat;
}

string Book::GetAuthorName() const{
    return authorName;
}
string Book::GetBookTitle() const{
    return bookTitle;
}
long Book::GetISBN() const{
    return isbn;
}
string Book::GetBookCategory() const {
    return category;
}
string Book::GetItemType() const {
    return "Book";
}



void Book::InputDetails() {
    cout << "Enter the Book's author: ";
    getline(cin, authorName);

    cout << "Enter the Book's title: ";
    getline(cin, bookTitle);
    
    cout << "Enter the Book's category (Biography, Fiction, SciFi, History, etc.): ";
    getline(cin, category);

    // Error handling for book cost input
    while (true) {
        cout << "Enter the Book's cost (up to 9 digits with at most 2 decimal places): ";
        string input;
        getline(cin, input);

        // Trim leading/trailing whitespace
        input.erase(0, input.find_first_not_of(" \t"));
        input.erase(input.find_last_not_of(" \t") + 1);

        if (!regex_match(input, regex(R"(\d{1,9}(\.\d{1,2})?)"))) {
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        cost = stod(input);
        if (cost < 0) {
            cout << "Cost cannot be negative. Try again.\n";
            continue;
        }
        break;
    }

    cout << "Book added successfully.\n";
}

void Book::EditDetails() {
    int choice;
    bool doneEditing = false;

    while (!doneEditing) {
        cout << "\nEditing Book with Library ID: " << libraryID << endl;
        cout << "1. Author Name\n"
             << "2. Book Title\n"
             << "3. Cost\n"
             << "4. Current Status\n"
             << "5. Loan Period\n"
             << "6. Done editing\n"
             << "Enter choice: ";

        if (!(cin >> choice) || choice < 1 || choice > 6) {
            cout << "Invalid choice. Please enter a number between 1 and 6.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(); // Clear newline character after choice

        switch (choice) {
            case 1: {
                cout << "Enter new Author Name: ";
                getline(cin, authorName);
                cout << "Author updated.\n";
                break;
            }
            case 2: {
                cout << "Enter new Book Title: ";
                getline(cin, bookTitle);
                cout << "Title updated.\n";
                break;
            }
            case 3: {
                string input;
                while (true) {
                    cout << "Enter new Cost (up to 9 digits, max 2 decimals): ";
                    getline(cin, input);
                    if (!regex_match(input, regex(R"(\d{1,9}(\.\d{1,2})?)"))) {
                        cout << "Invalid input. Try again.\n";
                        continue;
                    }
                    cost = stod(input);
                    if (cost < 0) {
                        cout << "Cost cannot be negative.\n";
                        continue;
                    }
                    cout << "Cost updated.\n";
                    break;
                }
                break;
            }
            case 4: {
                cout << "Enter new Status (In, Out, Lost): ";
                getline(cin, status);
                cout << "Status updated.\n";
                break;
            }
            case 5: {
                string input;
                while (true) {
                    cout << "Enter new Loan Period (days): ";
                    getline(cin, input);
                    try {
                        loanPeriod = stoi(input);
                        if (loanPeriod < 0) throw invalid_argument("Negative");
                        break;
                    } catch (...) {
                        cout << "Invalid loan period. Please enter a non-negative number.\n";
                    }
                }
                cout << "Loan Period updated.\n";
                break;
            }
            case 6:
                doneEditing = true;
                cout << "Finished editing.\n";
                break;
        }
    }
}

void Book::PrintHeader(ostream& os) const {
    os << "Book Details:" << endl << endl;
    os << left << setw(15) << "Category"
       << setw(20) << "ID"
       << setw(30) << "Author"
       << setw(30) << "Title"
       << setw(14) << "ISBN"
       << setw(15) << "Cost"
       << setw(20) << "Loan Period(days)"
       << setw(12) << "Status" << endl;
    os << setfill('-') << setw(160) << "-" << endl;
    os << setfill(' ');
}
void Book::PrintDetails(ostream& os) const {
    os << left << setw(15) << GetBookCategory()
       << setw(20) << GetLibraryID()
       << setw(30) << GetAuthorName()
       << setw(30) << GetBookTitle()
       << setw(14) << GetISBN()
       << "$" << setw(14) << fixed << setprecision(2) << GetCost()
       << setw(20) << GetLoanPeriod()
       << setw(12) << GetStatus() << endl;
}

bool Book::Matches(int criteria, const string& value) const {
    switch (criteria) {
        case 1: { // Status
            string bookStatus = status;
            string searchStatus = value;
            transform(bookStatus.begin(), bookStatus.end(), bookStatus.begin(), ::tolower);
            transform(searchStatus.begin(), searchStatus.end(), searchStatus.begin(), ::tolower);
            return bookStatus == searchStatus;
        }
        case 2: { // Library ID
            int searchID = stoi(value);
            return libraryID == searchID;
        }
        case 3: { // Loan Period
            int searchPeriod = stoi(value);
            return loanPeriod == searchPeriod;
        }
        default:
            return false;
    }
}


// Serialize book data to a string for file storage
string Book::serialize() const {
    stringstream ss;
    ss << bookTitle << "|" << authorName << "|" << isbn << "|" 
       << libraryID << "|" << cost << "|" << status << "|" << category << "|" << loanPeriod;
    return ss.str();
}


// Deserialize book data from a file
bool Book::deserialize(istream& inFile) {
    string line;
    if (getline(inFile, line)) {
        stringstream ss(line);

        string tempISBN, tempLibraryID, tempBookCost, tempLoanPeriod;

        getline(ss, bookTitle, '|');
        getline(ss, authorName, '|');
        getline(ss, tempISBN, '|');
        getline(ss, tempLibraryID, '|');
        getline(ss, tempBookCost, '|');
        getline(ss, status, '|');
        getline(ss, category, '|');
        getline(ss, tempLoanPeriod);

        isbn = stol(tempISBN);
        libraryID = stoi(tempLibraryID);
        cost = stod(tempBookCost);
        loanPeriod = stoi(tempLoanPeriod);

        return true;
    }
    return false;
}
