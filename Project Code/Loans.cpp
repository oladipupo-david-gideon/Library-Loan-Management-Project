#include "LibraryItems.h"
#include "Patrons.h"
#include "Loans.h"
#include "LibraryClock.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <random>

using namespace std;

vector<Loan>& Loans::GetLoanList(){
    return loanList;
}

int Loans::GenerateUniqueLoanID(){
    static vector<int> usedIDs; // Stores previously used IDs
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(10000, 99999); // 5-digit range

    int id;
    do {
        id = dist(gen); // Generate a random 5-digit number
    } while (find(usedIDs.begin(), usedIDs.end(), id) != usedIDs.end()); // Ensure uniqueness

    usedIDs.push_back(id); // Store the new ID
    return id;
}

bool Loans::IsLoanOverdue(int loanID) {
    string currentDate = LibraryClock::getCurrentDate();

    // Extract current date values
    int currDay, currMonth, currYear;
    if (sscanf(currentDate.c_str(), "%d/%d/%d", &currMonth, &currDay, &currYear) != 3) {
        cerr << "Error: Failed to parse current date!" << endl;
        return false;
    }

    // Find the loan with loanID
    auto loanIt = find_if(loanList.begin(), loanList.end(), [loanID](const Loan& loan) {
        return loan.GetLoanID() == loanID;
    });

    if (loanIt == loanList.end()) {
        cerr << "Error: Loan ID " << loanID << " not found!" << endl;
        return false;
    }

    string dueDate = loanIt->GetDueDate();

    // Extract due date values
    int dueDay, dueMonth, dueYear;
    if (sscanf(dueDate.c_str(), "%d/%d/%d", &dueMonth, &dueDay, &dueYear) != 3) {
        cerr << "Error: Failed to parse due date for Loan ID " << loanID << endl;
        return false;
    }

    // Compare dates correctly (Year -> Month -> Day)
    return (dueYear < currYear) ||
           (dueYear == currYear && dueMonth < currMonth) ||
           (dueYear == currYear && dueMonth == currMonth && dueDay < currDay);
}

//Checks if patron has any overdue loans 
bool Loans::IsPatronOverdue(int patronID) {
    string currentDate = LibraryClock::getCurrentDate();

    // Extract current date values
    int currDay, currMonth, currYear;
    if (sscanf(currentDate.c_str(), "%d/%d/%d", &currMonth, &currDay, &currYear) != 3) {
        cerr << "Error: Failed to parse current date!" << endl;
        return false;
    }

    for (const auto& loan : loanList) {
        // Skip loans that don't belong to the patron
        if (loan.GetPatronID() != patronID) continue;

        string dueDate = loan.GetDueDate();

        // Extract due date values
        int dueDay, dueMonth, dueYear;
        if (sscanf(dueDate.c_str(), "%d/%d/%d", &dueMonth, &dueDay, &dueYear) != 3) {
            cerr << "Error: Failed to parse due date for Loan ID " 
                 << loan.GetLoanID() << endl;
            continue;  // Skip this loan if parsing fails
        }

        // Compare dates correctly (Year -> Month -> Day)
        if ((dueYear < currYear) ||
            (dueYear == currYear && dueMonth < currMonth) ||
            (dueYear == currYear && dueMonth == currMonth && dueDay < currDay)) {
            
            return true; // The patron has at least one overdue loan
        }
    }

    return false; // No overdue loans found
}

//Checks if patron has other overdue loans beside the one with the loanID
bool Loans::HasOtherLoansOverdue(int loanID) {
    string currentDate = LibraryClock::getCurrentDate();

    // Extract current date values
    int currDay, currMonth, currYear;
    if (sscanf(currentDate.c_str(), "%d/%d/%d", &currMonth, &currDay, &currYear) != 3) {
        cerr << "Error: Failed to parse current date!" << endl;
        return false;
    }

    // Find the loan with loanID to get the associated patron
    auto loanIt = find_if(loanList.begin(), loanList.end(), [loanID](const Loan& loan) {
        return loan.GetLoanID() == loanID;
    });

    if (loanIt == loanList.end()) {
        cerr << "Error: Loan ID " << loanID << " not found!" << endl;
        return false;
    }

    int patronID = loanIt->GetPatronID(); // Get the patron's ID

    // Now check if the patron has any other overdue loans
    for (const auto& loan : loanList) {
        // Skip the loan with the given loanID
        if (loan.GetLoanID() == loanID) continue;

        // Skip loans not belonging to the same patron
        if (loan.GetPatronID() != patronID) continue;

        string dueDate = loan.GetDueDate();

        // Extract due date values
        int dueDay, dueMonth, dueYear;
        if (sscanf(dueDate.c_str(), "%d/%d/%d", &dueMonth, &dueDay, &dueYear) != 3) {
            cerr << "Error: Failed to parse due date for Loan ID " 
                 << loan.GetLoanID() << endl;
            continue;  // Skip this loan if parsing fails
        }

        // Compare dates correctly (Year -> Month -> Day)
        if ((dueYear < currYear) ||
            (dueYear == currYear && dueMonth < currMonth) ||
            (dueYear == currYear && dueMonth == currMonth && dueDay < currDay)) {
            
            return true; // Found another overdue loan
        }
    }

    return false; // No other overdue loans found
}

void Loans::updatePatronFineBalByClock(int loanID, vector<Patron>& patronL) {
    if (!IsLoanOverdue(loanID)) {
        return; // Loan is not overdue, no fine update needed
    }

    string currentDate = LibraryClock::getCurrentDate();

    // Extract current date values
    int currDay, currMonth, currYear;
    if (sscanf(currentDate.c_str(), "%d/%d/%d", &currMonth, &currDay, &currYear) != 3) {
        cerr << "Error: Failed to parse current date!" << endl;
        return;
    }

    // Find the loan with loanID
    auto loanIt = find_if(loanList.begin(), loanList.end(), [loanID](const Loan& loan) {
        return loan.GetLoanID() == loanID;
    });

    if (loanIt == loanList.end()) {
        cerr << "Error: Loan ID " << loanID << " not found!" << endl;
        return;
    }

    string dueDate = loanIt->GetDueDate();

    // Extract due date values
    int dueDay, dueMonth, dueYear;
    if (sscanf(dueDate.c_str(), "%d/%d/%d", &dueMonth, &dueDay, &dueYear) != 3) {
        cerr << "Error: Failed to parse due date for Loan ID " << loanID << endl;
        return;
    }

    // Calculate overdue days
    tm dueTm = {};
    dueTm.tm_mday = dueDay;
    dueTm.tm_mon = dueMonth - 1;
    dueTm.tm_year = dueYear - 1900;

    tm currTm = {};
    currTm.tm_mday = currDay;
    currTm.tm_mon = currMonth - 1;
    currTm.tm_year = currYear - 1900;

    time_t dueTime = mktime(&dueTm);
    time_t currTime = mktime(&currTm);

    if (dueTime == -1 || currTime == -1) {
        cerr << "Error: Failed to compute overdue days!" << endl;
        return;
    }

    int overdueDays = (currTime - dueTime) / (60 * 60 * 24); // Convert seconds to days

    if (overdueDays <= 0) {
        return; // No fine if overdue days are zero or negative
    }

    // Find the patron in patronL
    int patronID = loanIt->GetPatronID();
    auto patronIt = find_if(patronL.begin(), patronL.end(), [patronID](Patron& patron) {
        return patron.GetPatronID() == patronID;
    });

    if (patronIt == patronL.end()) {
        cerr << "Error: Patron ID " << patronID << " not found!" << endl;
        return;
    }

    // **Fix: Only add fine for newly overdue days**
    int prevOverdueDays = loanIt->GetPreviousOverdueDays(); // Store the last recorded overdue days (add this function)
    int newOverdueDays = overdueDays - prevOverdueDays; // Get only the new overdue days

    if (newOverdueDays > 0) { // Ensure we only add fines if there's a new overdue day
        double fineAmount = newOverdueDays * 0.25; // $0.25 per newly overdue day
        patronIt->IncreaseFineBalance(fineAmount);
        loanIt->SetPreviousOverdueDays(overdueDays); // Update the last recorded overdue days
    }
}


void Loans::CheckOutItem(int patronID, int itemID, vector<Patron>& patronL, vector<LibraryItem*>& itemL) {
    auto patronit = find_if(patronL.begin(), patronL.end(), [patronID](const Patron& p) {
        return p.GetPatronID() == patronID;
    });

    if (patronit == patronL.end()) {
        cout << "Patron with ID " << patronID << " not found.\n";
        return;
    }

    if (patronit->GetBooksOut() == 6) {
        cout << "Patron has checked out maximum number of items.\n";
        return;
    }

    if (IsPatronOverdue(patronID)) {
        cout << "Patron has overdue items.\n";
        return;
    }

    if (patronit->GetBooksOut() > 0) {
        cout << "List of all loans for patron:\n";
        AllLoansForPatron(patronID);
    }

    auto itemit = find_if(itemL.begin(), itemL.end(), [itemID](LibraryItem* item) {
        return item->GetLibraryID() == itemID;
    });

    if (itemit == itemL.end()) {
        cout << "Item with ID " << itemID << " not found.\n";
        return;
    }

    Loan tempLoan;
    tempLoan.SetLoanID(GenerateUniqueLoanID());
    tempLoan.SetItemID(itemID);
    tempLoan.SetPatronID(patronID);
    tempLoan.SetLoanStatus("Normal");
    tempLoan.SetDueDate();
    tempLoan.SetNumRechecks(0);
    loanList.push_back(tempLoan);

    (*itemit)->SetStatus("Out");
    patronit->IncreaseBooksCheckedOut();

    cout << "Item with ID " << itemID << " checked out successfully.\n";
    cout << "Due date: " << tempLoan.GetDueDate() << endl;
}
void Loans::CheckInItem(int loanID, vector<Patron>& patronL, vector<LibraryItem*>& itemL) {
    auto loanit = find_if(loanList.begin(), loanList.end(), [loanID](const Loan& l) {
        return l.GetLoanID() == loanID;
    });

    if (loanit == loanList.end()) {
        cout << "Loan with ID " << loanID << " not found.\n";
        return;
    }

    int patronID = loanit->GetPatronID();
    int itemID = loanit->GetItemID();

    auto patronit = find_if(patronL.begin(), patronL.end(), [patronID](Patron& p) {
        return p.GetPatronID() == patronID;
    });

    if (patronit != patronL.end()) {
        patronit->DecreaseBooksCheckedOut();
    }

    auto itemit = find_if(itemL.begin(), itemL.end(), [itemID](LibraryItem* item) {
        return item->GetLibraryID() == itemID;
    });

    if (itemit != itemL.end()) {
        (*itemit)->SetStatus("In");
    }

    loanList.erase(loanit);
    cout << "Item under loan ID " << loanID << " has been checked in successfully.\n";
}
void Loans::ReCheckItem(int loanID, vector<Patron>& patronL, vector<LibraryItem*>& itemL) {
    auto loanit = find_if(loanList.begin(), loanList.end(), [loanID](const Loan& l) {
        return l.GetLoanID() == loanID;
    });

    if (loanit == loanList.end()) {
        cout << "Loan with ID " << loanID << " not found.\n";
        return;
    }

    if (loanit->GetNumRechecks() == 1) {
        cout << "Item has already been rechecked once.\n";
        return;
    }

    int patronID = loanit->GetPatronID();

    auto patronit = find_if(patronL.begin(), patronL.end(), [patronID](Patron& p) {
        return p.GetPatronID() == patronID;
    });

    if (patronit->GetBooksOut() == 6) {
        cout << "Patron has maxed out checkouts.\n";
        AllLoansForPatron(patronID);
        return;
    }

    if (HasOtherLoansOverdue(loanit->GetLoanID())) {
        cout << "Patron has other overdue items.\n";
        AllLoansForPatron(patronID);
        return;
    }

    AllLoansForPatron(patronID);

    loanit->SetDueDate();
    loanit->SetLoanStatus("Normal");
    loanit->SetNumRechecks(1);

    cout << "Item with ID " << loanit->GetItemID() << " rechecked successfully. New due date: " << loanit->GetDueDate() << endl;
}


void Loans::OverdueLoansForPatron(int pID) {
    string currentDate = LibraryClock::getCurrentDate();
    int currDay, currMonth, currYear;

    if (sscanf(currentDate.c_str(), "%d/%d/%d", &currMonth, &currDay, &currYear) != 3) {
        cerr << "Error: Failed to parse current date!" << endl;
        return;
    }

    bool patronExists = false;
    bool hasOverdue = false;

    cout << "Checking overdue items for Patron ID: " << pID << " as of " << currentDate << "...\n";

    // Check each loan
    for (const auto& loan : loanList) {
        if (loan.GetPatronID() == pID) {
            patronExists = true;

            string dueDate = loan.GetDueDate();
            int dueDay, dueMonth, dueYear;

            if (sscanf(dueDate.c_str(), "%d/%d/%d", &dueMonth, &dueDay, &dueYear) != 3) {
                cerr << "Error: Failed to parse due date for Loan ID " << loan.GetLoanID() << endl;
                continue;
            }

            if ((dueYear < currYear) || (dueYear == currYear && dueMonth < currMonth) ||
                (dueYear == currYear && dueMonth == currMonth && dueDay < currDay)) {
                
                if (!hasOverdue) {
                    cout << left << setw(10) << "Loan ID" 
                        << setw(20) << "Patron ID" 
                        << setw(15) << "Item ID"
                        << setw(14) << "Loan Status" 
                        << setw(12) << "Due Date" 
                        << setw(16) << "Number of Rechecks" << endl;
                    cout << setfill('-') << setw(110) << "-" << endl;
                    cout << setfill(' ');
                    hasOverdue = true;
                }

                // Print overdue loan details
                cout << left << setw(10) << loan.GetLoanID()
                     << setw(20) << loan.GetPatronID()
                     << setw(15) << loan.GetItemID()
                     << setw(14) << loan.GetLoanStatus()
                     << setw(12) << loan.GetDueDate()
                     << setw(6) << loan.GetNumRechecks() << endl;
            }
        }
    }

    if (!patronExists) {
        cout << "Error: Patron with ID " << pID << " does not exist." << endl;
    } else if (!hasOverdue) {
        cout << "Patron has no overdue books as of " << currentDate << "." << endl;
    }
}
void Loans::PrintAllLoans(){
    if (loanList.empty()) {
        cout << "There are no loans currently in the system." << endl;
        return;
    }

    cout << "Displaying all library loans:" << endl;

    cout << left << setw(10) << "Loan ID" 
    << setw(20) << "Patron ID" 
    << setw(15) << "Item ID"
    << setw(14) << "Loan Status" 
    << setw(12) << "Due Date" 
    << setw(16) << "Number of Rechecks" << endl;
    cout << setfill('-') << setw(110) << "-" << endl;
    cout << setfill(' ');

    for (const auto& loan : loanList) {
        cout << left << setw(10) << loan.GetLoanID()
        << setw(20) << loan.GetPatronID() 
        << setw(15) << loan.GetItemID()
        << setw(14) << loan.GetLoanStatus()
        << setw(12) << loan.GetDueDate()
        << setw(16) << loan.GetNumRechecks() << endl;
    }
}

void Loans::ListOverdueLoans() {
    string currentDate = LibraryClock::getCurrentDate();
    bool hasOverdue = false; // Flag to track if any overdue books exist

    // Extract current date values
    int currDay, currMonth, currYear;
    if (sscanf(currentDate.c_str(), "%d/%d/%d", &currMonth, &currDay, &currYear) != 3) {
        cerr << "Error: Failed to parse current date!" << endl;
        return;
    }

    // First pass: Check if any loans are overdue
    for (const auto& loan : loanList) {
        string dueDate = loan.GetDueDate();
        int dueDay, dueMonth, dueYear;
        
        if (sscanf(dueDate.c_str(), "%d/%d/%d", &dueMonth, &dueDay, &dueYear) != 3) {
            cerr << "Error: Failed to parse due date for Loan ID " << loan.GetLoanID() << endl;
            continue;  
        }

        string tempStat = loan.GetLoanStatus();
        transform(tempStat.begin(), tempStat.end(), tempStat.begin(), ::tolower);

        if ((dueYear < currYear) ||
            (dueYear == currYear && dueMonth < currMonth) ||
            (dueYear == currYear && dueMonth == currMonth && dueDay < currDay) || (tempStat == "overdue")) {
            hasOverdue = true;
            break; // No need to check further, we just need to know if at least one exists
        }
    }

    // If no overdue books were found, print the message and return
    if (!hasOverdue) {
        cout << "There are no overdue items as of " << currentDate << "." << endl;
        return;
    }

    // If there are overdue books, print the header first
    cout << "Overdue Items as of " << currentDate << ":\n";
    cout << left << setw(10) << "Loan ID" 
         << setw(20) << "Patron ID" 
         << setw(15) << "Item ID"
         << setw(14) << "Loan Status" 
         << setw(12) << "Due Date" 
         << setw(16) << "Number of Rechecks" << endl;
    cout << setfill('-') << setw(110) << "-" << endl;
    cout << setfill(' ');

    // Second pass: Print overdue books
    for (const auto& loan : loanList) {
        string dueDate = loan.GetDueDate();
        int dueDay, dueMonth, dueYear;
        
        if (sscanf(dueDate.c_str(), "%d/%d/%d", &dueMonth, &dueDay, &dueYear) != 3) {
            cerr << "Error: Failed to parse due date for Loan ID " << loan.GetLoanID() << endl;
            continue;  
        }

        if ((dueYear < currYear) ||
            (dueYear == currYear && dueMonth < currMonth) ||
            (dueYear == currYear && dueMonth == currMonth && dueDay < currDay)) {
            
            // Loan is overdue, print it
            cout << left << setw(10) << loan.GetLoanID()
                 << setw(20) << loan.GetPatronID() 
                 << setw(15) << loan.GetItemID()
                 << setw(14) << loan.GetLoanStatus()
                 << setw(12) << loan.GetDueDate()
                 << setw(16) << loan.GetNumRechecks() << endl;
        }
    }
}
void Loans::AllLoansForPatron(int patronID) {
    bool patronExists = false;
    bool hasLoans = false;

    cout << "Retrieving loans for Patron ID: " << patronID << "...\n";

    for (const auto& loan : loanList) {
        if (loan.GetPatronID() == patronID) {
            if (!hasLoans) {
                cout << left << setw(10) << "Loan ID" 
                    << setw(20) << "Patron ID" 
                    << setw(15) << "Item ID"
                    << setw(14) << "Loan Status" 
                    << setw(12) << "Due Date" 
                    << setw(16) << "Number of Rechecks" << endl;
                cout << setfill('-') << setw(110) << "-" << endl;
                cout << setfill(' ');
                hasLoans = true;
            }

            cout << left << setw(10) << loan.GetLoanID()
                 << setw(20) << loan.GetPatronID()
                 << setw(15) << loan.GetItemID()
                 << setw(14) << loan.GetLoanStatus()
                 << setw(12) << loan.GetDueDate()
                 << setw(6) << loan.GetNumRechecks() << endl;
        }
    }

    if (!hasLoans) {
        cout << "No loans found for Patron ID: " << patronID << "." << endl;
    }
}

//Update a single loan's data according to system clock (loanStatus, 
//fineBal )
void Loans::UpdateLoanStatus(int loanID, vector<Patron>& patronL){
    // Find the loan based on the loanID
    auto loanit = find_if(loanList.begin(), loanList.end(), [loanID](const Loan& l) {
        return l.GetLoanID() == loanID;
    });

    if (loanit != loanList.end()) {
        //Check if loan is overdue, update loan status if true
        if(IsLoanOverdue(loanID)){
            loanit->SetLoanStatus("Overdue");
        }
        else{
            loanit->SetLoanStatus("Normal");
        }

        //update patron fineBalance according to sytem clock
        updatePatronFineBalByClock(loanID, patronL);
    }
    else{
        cout << "Loan with ID " << loanID << " was not found." << endl;
        return;
    }
}

//Update all loan's data according to system clock
void Loans::UpdateAllLoans(vector<Patron>& patronL) {
    for (auto& loan : loanList) { // Remove 'const' to allow modifications
        this->UpdateLoanStatus(loan.GetLoanID(), patronL);
    }
}
void Loans::EditLoan(int loanID){
    // Find the loan based on the loan ID
    auto loanit = find_if(loanList.begin(), loanList.end(), [loanID](const Loan& l) {
        return l.GetLoanID() == loanID;
    });

    if (loanit != loanList.end()) {
        Loan& loan = *loanit; // Found loan

        // Begin editing menu
        int choice;
        bool doneEditing = false;

        while (!doneEditing) {
            cout << "\nEditing Loan with Loan ID: " << loanID << endl;
            cout << "What would you like to edit?" << endl;
            cout << "1. Loan Status" << endl;
            cout << "2. Done editing" << endl;
            cout << "Enter your choice (1-2): ";
            cin >> choice;
            cin.clear(); // Clear any error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer

            switch (choice) {
                case 1: {
                    string newLoanStatus;
                    cout << "Enter new Loan Status (Normal or Overdue): ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Fix issue with getline()
                    getline(cin, newLoanStatus);
                    loan.SetLoanStatus(newLoanStatus);
                    cout << "Loan Status updated successfully." << endl;
                    break;
                }
                case 2:
                    doneEditing = true;
                    cout << "Finished editing the loan details." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please enter 1 or 2." << endl;
            }
        }
    } else {
        cout << "Loan with ID " << loanID << " not found." << endl;
    }
}
void Loans::ReportLostItem(int loanID, vector<Patron>& patronL, vector<LibraryItem*>& itemL) {
    auto loanit = find_if(loanList.begin(), loanList.end(), [loanID](const Loan& l) {
        return l.GetLoanID() == loanID;
    });

    if (loanit == loanList.end()) {
        cout << "Loan with ID " << loanID << " not found.\n";
        return;
    }

    int patronID = loanit->GetPatronID();
    int itemID = loanit->GetItemID();

    auto patronit = find_if(patronL.begin(), patronL.end(), [patronID](Patron& p) {
        return p.GetPatronID() == patronID;
    });

    auto itemit = find_if(itemL.begin(), itemL.end(), [itemID](LibraryItem* item) {
        return item->GetLibraryID() == itemID;
    });

    if (patronit != patronL.end() && itemit != itemL.end()) {
        patronit->IncreaseFineBalance((*itemit)->GetCost());
        patronit->DecreaseBooksCheckedOut();
        (*itemit)->SetStatus("Lost");
    }

    loanList.erase(loanit);
    cout << "Item with ID " << itemID << " has been reported lost.\n";
}

// Save loans to file
void Loans::saveToFile() const {
    ofstream file("loans.txt");
    for (const auto& loan : loanList) {
        file << loan.serialize() << endl;
    }
}

void Loans::EnsureFileExists(const string& filename) {
    // Open file in append mode: creates file if missing, does nothing if it exists
    ofstream outFile(filename, ios::app);  
    outFile.close();  // Close the file immediately without writing
}
// Load loans from file
void Loans::loadFromFile() {
    EnsureFileExists("loans.txt");  // Ensures the file exists

    ifstream file("loans.txt");
    Loan tempLoan;
    while (tempLoan.deserialize(file)) {
        loanList.push_back(tempLoan);
    }
}
