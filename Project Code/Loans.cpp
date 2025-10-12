#include "Loans.h"
#include "LibraryClock.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <vector>
#include <iomanip>
#include <cstdio> // For sscanf

bool Loans::isDatePast(const Date& date) const {
    std::string currentDateStr = LibraryClock::getCurrentDate();
    int currMonth, currDay, currYear;
    sscanf(currentDateStr.c_str(), "%d/%d/%d", &currMonth, &currDay, &currYear);

    if (currYear > date.year) return true;
    if (currYear == date.year && currMonth > date.month) return true;
    if (currYear == date.year && currMonth == date.month && currDay > date.day) return true;
    
    return false;
}

int Loans::GenerateUniqueLoanID() {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(10000, 99999);
    int id;
    bool isUnique;
    do {
        id = dist(gen);
        isUnique = true;
        for (const auto& loan : loanList) {
            if (loan.GetLoanID() == id) {
                isUnique = false;
                break;
            }
        }
    } while (!isUnique);
    return id;
}

void Loans::CheckOutItem(int patronID, int itemID, Patrons& patrons, LibraryItems& items) {
    auto& patronList = patrons.GetPatronList();
    auto patronIt = std::find_if(patronList.begin(), patronList.end(), 
        [patronID](const Patron& p) { return p.GetPatronID() == patronID; });
    if (patronIt == patronList.end()) {
        std::cout << "Error: Patron not found.\n";
        return;
    }

    auto& itemList = items.GetLibraryItems();
    auto itemIt = std::find_if(itemList.begin(), itemList.end(), 
        [itemID](const auto& i) { return i->GetLibraryID() == itemID; });
    if (itemIt == itemList.end()) {
        std::cout << "Error: Item not found.\n";
        return;
    }

    if ((*itemIt)->GetStatus() != "In") {
        std::cout << "Error: Item is currently unavailable.\n";
        return;
    }
    if (patronIt->GetFineBalance() > 0) {
        std::cout << "Error: Patron has outstanding fines.\n";
        return;
    }

    Loan newLoan;
    newLoan.SetLoanID(GenerateUniqueLoanID());
    newLoan.SetItemID(itemID);
    newLoan.SetPatronID(patronID);
    newLoan.SetDueDate((*itemIt)->GetLoanPeriod());
    
    loanList.push_back(newLoan);

    (*itemIt)->SetStatus("Out");
    patronIt->IncrementItemsOut();

    std::cout << "Item " << itemID << " checked out successfully to patron " << patronID << ".\n";
    std::cout << "Due Date: " << newLoan.GetDueDateAsString() << std::endl;
}

void Loans::CheckInItem(int loanID, Patrons& patrons, LibraryItems& items) {
    auto loanIt = std::find_if(loanList.begin(), loanList.end(), 
        [loanID](const Loan& l) { return l.GetLoanID() == loanID; });
    if (loanIt == loanList.end()) {
        std::cout << "Error: Loan ID not found.\n";
        return;
    }

    int patronID = loanIt->GetPatronID();
    int itemID = loanIt->GetItemID();

    auto& patronList = patrons.GetPatronList();
    auto patronIt = std::find_if(patronList.begin(), patronList.end(), 
        [patronID](const Patron& p) { return p.GetPatronID() == patronID; });
    if (patronIt != patronList.end()) {
        patronIt->DecrementItemsOut();
    }

    auto& itemList = items.GetLibraryItems();
    auto itemIt = std::find_if(itemList.begin(), itemList.end(), 
        [itemID](const auto& i) { return i->GetLibraryID() == itemID; });
    if (itemIt != itemList.end()) {
        (*itemIt)->SetStatus("In");
        if (loanIt->GetLoanStatus() == "Overdue") {
            std::cout << "Item was overdue. Please check patron for fines.\n";
        }
    }

    loanList.erase(loanIt);
    std::cout << "Loan " << loanID << " has been checked in.\n";
}

void Loans::PrintAllLoans() {
    if (loanList.empty()) {
        std::cout << "There are no active loans." << std::endl;
        return;
    }
    std::cout << "\n--- ALL LOANS ---\n";
    std::cout << std::left << std::setw(10) << "Loan ID"
              << std::setw(10) << "Item ID"
              << std::setw(12) << "Patron ID"
              << std::setw(15) << "Due Date"
              << std::setw(10) << "Status" << std::endl;
    std::cout << std::string(57, '-') << std::endl;
    for (const auto& loan : loanList) {
        std::cout << std::left << std::setw(10) << loan.GetLoanID()
                  << std::setw(10) << loan.GetItemID()
                  << std::setw(12) << loan.GetPatronID()
                  << std::setw(15) << loan.GetDueDateAsString()
                  << std::setw(10) << loan.GetLoanStatus() << std::endl;
    }
}

void Loans::ListOverdueLoans() {
    bool found = false;
    for (const auto& loan : loanList) {
        if (loan.GetLoanStatus() == "Overdue") {
            if (!found) {
                std::cout << "\n--- OVERDUE LOANS ---\n";
                std::cout << std::left << std::setw(10) << "Loan ID" << std::setw(10) << "Item ID" << std::setw(12) << "Patron ID" << std::setw(15) << "Due Date" << std::endl;
                std::cout << std::string(47, '-') << std::endl;
                found = true;
            }
            std::cout << std::left << std::setw(10) << loan.GetLoanID()
                      << std::setw(10) << loan.GetItemID()
                      << std::setw(12) << loan.GetPatronID()
                      << std::setw(15) << loan.GetDueDateAsString() << std::endl;
        }
    }
    if (!found) {
        std::cout << "There are no overdue loans.\n";
    }
}

void Loans::AllLoansForPatron(int patronID) {
    bool found = false;
    for (const auto& loan : loanList) {
        if (loan.GetPatronID() == patronID) {
            if (!found) {
                std::cout << "\n--- LOANS FOR PATRON " << patronID << " ---\n";
                std::cout << std::left << std::setw(10) << "Loan ID" << std::setw(10) << "Item ID" << std::setw(15) << "Due Date" << std::setw(10) << "Status" << std::endl;
                std::cout << std::string(45, '-') << std::endl;
                found = true;
            }
            std::cout << std::left << std::setw(10) << loan.GetLoanID()
                      << std::setw(10) << loan.GetItemID()
                      << std::setw(15) << loan.GetDueDateAsString()
                      << std::setw(10) << loan.GetLoanStatus() << std::endl;
        }
    }
    if (!found) {
        std::cout << "No loans found for patron ID " << patronID << ".\n";
    }
}

void Loans::UpdateAllLoanStatuses(Patrons& patrons) {
    for (auto& loan : loanList) {
        if (loan.GetLoanStatus() != "Lost" && isDatePast(loan.GetDueDate())) {
            if (loan.GetLoanStatus() != "Overdue") {
                 loan.SetLoanStatus("Overdue");
                 auto& patronList = patrons.GetPatronList();
                 auto patronIt = std::find_if(patronList.begin(), patronList.end(),
                     [&](const Patron& p){ return p.GetPatronID() == loan.GetPatronID(); });
                 if (patronIt != patronList.end()) {
                     patronIt->AdjustFineBalance(1.00); // Add a $1.00 fine
                 }
            }
        }
    }
}

void Loans::saveToFile() {
    std::ofstream outFile("loans.txt");
    if (!outFile) {
        std::cerr << "Error opening loans.txt for writing." << std::endl;
        return;
    }
    for (const auto& loan : loanList) {
        outFile << loan.serialize() << std::endl;
    }
}
void Loans::loadFromFile() {
    std::ifstream inFile("loans.txt");
    if (!inFile) {
        return;
    }
    Loan tempLoan;
    while (tempLoan.deserialize(inFile)) {
        loanList.push_back(tempLoan);
    }
}