#include "DVD.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <regex>
#include <limits>
#include <algorithm>

using namespace std;

// Constructor
DVD::DVD() {
    title = "unknown";
    category = "unknown";
    runTime = 0;
    studio = "unknown";
    releaseDate = "unknown";
    libraryID = 0;
    cost = 0.00;
    status = "none";
    loanPeriod = 0;
}

// Setters
void DVD::SetTitle(const string& t) {
    title = t;
}

void DVD::SetCategory(const string& c) {
    category = c;
}

void DVD::SetRunTime(int rt) {
    runTime = rt;
}

void DVD::SetStudio(const string& s) {
    studio = s;
}

void DVD::SetReleaseDate(const string& rd) {
    releaseDate = rd;
}

// Getters
string DVD::GetTitle() const {
    return title;
}

string DVD::GetCategory() const {
    return category;
}

int DVD::GetRunTime() const {
    return runTime;
}

string DVD::GetStudio() const {
    return studio;
}

string DVD::GetReleaseDate() const {
    return releaseDate;
}

// Polymorphic overrides
string DVD::GetItemType() const {
    return "DVD";
}

void DVD::InputDetails() {
    cout << "Enter the DVD Title: ";
    getline(cin, title);

    cout << "Enter the Category (Action, SciFi, Drama, etc.): ";
    getline(cin, category);

    cout << "Enter the Studio (Marvel, Pixar, Disney, etc.): ";
    getline(cin, studio);

    cout << "Enter the Release Date (mm/dd/yyyy): ";
    getline(cin, releaseDate);

    while (true) {
        cout << "Enter the Runtime in minutes: ";
        string input;
        getline(cin, input);
        try {
            runTime = stoi(input);
            if (runTime < 0) throw invalid_argument("Negative");
            break;
        } catch (...) {
            cout << "Invalid input. Try again.\n";
        }
    }

    while (true) {
        cout << "Enter the Cost (up to 9 digits with max 2 decimal places): ";
        string input;
        getline(cin, input);
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

    cout << "DVD added successfully.\n";
}

void DVD::EditDetails() {
    int choice;
    bool doneEditing = false;

    while (!doneEditing) {
        cout << "\nEditing DVD with Library ID: " << libraryID << endl;
        cout << "1. Title\n"
             << "2. Category\n"
             << "3. Studio\n"
             << "4. Release Date\n"
             << "5. Runtime\n"
             << "6. Cost\n"
             << "7. Status\n"
             << "8. Loan Period\n"
             << "9. Done editing\n"
             << "Enter choice: ";

        if (!(cin >> choice) || choice < 1 || choice > 9) {
            cout << "Invalid choice. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(); // clear newline

        switch (choice) {
            case 1: {
                cout << "Enter new Title: ";
                getline(cin, title);
                cout << "Title updated.\n";
                break;
            }
            case 2: {
                cout << "Enter new Category: ";
                getline(cin, category);
                cout << "Category updated.\n";
                break;
            }
            case 3: {
                cout << "Enter new Studio: ";
                getline(cin, studio);
                cout << "Studio updated.\n";
                break;
            }
            case 4: {
                cout << "Enter new Release Date (mm/dd/yyyy): ";
                getline(cin, releaseDate);
                cout << "Release Date updated.\n";
                break;
            }
            case 5: {
                string input;
                while (true) {
                    cout << "Enter new Runtime (minutes): ";
                    getline(cin, input);
                    try {
                        runTime = stoi(input);
                        if (runTime < 0) throw invalid_argument("Negative");
                        break;
                    } catch (...) {
                        cout << "Invalid input. Try again.\n";
                    }
                }
                cout << "Runtime updated.\n";
                break;
            }
            case 6: {
                string input;
                while (true) {
                    cout << "Enter new Cost: ";
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
                    break;
                }
                cout << "Cost updated.\n";
                break;
            }
            case 7: {
                cout << "Enter new Status (In, Out, Lost): ";
                getline(cin, status);
                cout << "Status updated.\n";
                break;
            }
            case 8: {
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
            case 9:
                doneEditing = true;
                cout << "Finished editing.\n";
                break;
        }
    }
}


void DVD::PrintHeader(ostream& os) const {
    os << "DVD Details:" << endl << endl;
    os << left << setw(12) << "ID"
         << setw(25) << "Title"
         << setw(20) << "Category"
         << setw(20) << "Studio"
         << setw(16) << "Release Date"
         << setw(12) << "Runtime"
         << setw(12) << "Cost"
         << setw(20) << "Loan Period(days)"
         << setw(12) << "Status"
         << endl;

    os << setfill('-') << setw(150) << "-" << endl;
    os << setfill(' ');
}
void DVD::PrintDetails(ostream& os) const {
    os << left << setw(12) << libraryID
         << setw(25) << title
         << setw(20) << category
         << setw(20) << studio
         << setw(16) << releaseDate
         << setw(12) << runTime
         << "$" << setw(11) << fixed << setprecision(2) << cost
         << setw(20) << loanPeriod
         << setw(12) << status
         << endl;
}

bool DVD::Matches(int criteria, const string& value) const {
    switch (criteria) {
        case 1: {
            string dvdStatus = status;
            string search = value;
            transform(dvdStatus.begin(), dvdStatus.end(), dvdStatus.begin(), ::tolower);
            transform(search.begin(), search.end(), search.begin(), ::tolower);
            return dvdStatus == search;
        }
        case 2:
            return libraryID == stoi(value);
        case 3:
            return loanPeriod == stoi(value);
        default:
            return false;
    }
}

// Serialize
string DVD::serialize() const {
    stringstream ss;
    ss << title << "|" << category << "|" << studio << "|" << releaseDate << "|"
       << runTime << "|" << libraryID << "|" << cost << "|" << status << "|" << loanPeriod;
    return ss.str();
}

// Deserialize
bool DVD::deserialize(istream& inFile) {
    string line;
    if (getline(inFile, line)) {
        stringstream ss(line);
        string tempRunTime, tempID, tempCost, tempLoan;

        getline(ss, title, '|');
        getline(ss, category, '|');
        getline(ss, studio, '|');
        getline(ss, releaseDate, '|');
        getline(ss, tempRunTime, '|');
        getline(ss, tempID, '|');
        getline(ss, tempCost, '|');
        getline(ss, status, '|');
        getline(ss, tempLoan);

        runTime = stoi(tempRunTime);
        libraryID = stoi(tempID);
        cost = stod(tempCost);
        loanPeriod = stoi(tempLoan);

        return true;
    }
    return false;
}
