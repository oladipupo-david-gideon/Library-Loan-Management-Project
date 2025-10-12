#include "LibraryItems.h"
#include "Patrons.h"
#include "Loans.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

// --- Function Prototypes ---
void handleItemsMenu(LibraryItems& library);
void handlePatronsMenu(Patrons& patrons);
void handleLoansMenu(Loans& loans, Patrons& patrons, LibraryItems& library);
void printMainMenu();

// --- Main Function ---
int main() {
    LibraryItems library;
    Patrons patrons;
    Loans loans;

    // Load all data from files
    library.loadFromFile();
    patrons.loadFromFile();
    loans.loadFromFile();

    // Update statuses on startup
    loans.UpdateAllLoanStatuses(patrons);

    int mainChoice;
    while (true) {
        printMainMenu();
        std::cin >> mainChoice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (mainChoice) {
            case 1:
                handleItemsMenu(library);
                break;
            case 2:
                handlePatronsMenu(patrons);
                break;
            case 3:
                handleLoansMenu(loans, patrons, library);
                break;
            case 4:
                std::cout << "Saving all data...\n";
                library.saveToFile();
                patrons.saveToFile();
                loans.saveToFile();
                std::cout << "Exiting program. Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }
    return 0;
}

// --- Menu Handlers & Print Functions ---
void printMainMenu() {
    std::cout << "\n--- Library Main Menu ---\n"
              << "1. Item Management\n"
              << "2. Patron Management\n"
              << "3. Loan Management\n"
              << "4. Save and Exit\n"
              << "Please select an option: ";
}

void handleItemsMenu(LibraryItems& library) {
    int choice;
    while(true) {
        std::cout << "\n--- Item Management ---\n"
                  << "1. Add New Item\n"
                  << "2. Delete Item\n"
                  << "3. Edit Item\n"
                  << "4. Find Item\n"
                  << "5. List All Items\n"
                  << "6. List Specific Item\n"
                  << "7. Return to Main Menu\n"
                  << "Option: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (choice == 7) break;
        
        int id;
        switch (choice) {
            case 1: library.AddItem(); break;
            case 2: 
                std::cout << "Enter ID of item to delete: ";
                std::cin >> id;
                library.DeleteItem(id);
                break;
            case 3:
                std::cout << "Enter ID of item to edit: ";
                std::cin >> id;
                library.EditItem(id);
                break;
            case 4: library.FindItem(); break;
            case 5: library.PrintAllItems(); break;
            case 6:
                std::cout << "Enter ID of item to show: ";
                std::cin >> id;
                library.PrintItem(id);
                break;
            default: std::cout << "Invalid choice.\n";
        }
    }
}

void handlePatronsMenu(Patrons& patrons) {
    int choice;
    while(true) {
        std::cout << "\n--- Patron Management ---\n"
                  << "1. Add New Patron\n"
                  << "2. Edit Patron\n"
                  << "3. Find Patron\n"
                  << "4. List All Patrons\n"
                  << "5. List Patrons with Fines\n"
                  << "6. Pay Fines\n"
                  << "7. Return to Main Menu\n"
                  << "Option: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 7) break;
        
        int id;
        switch (choice) {
            case 1: patrons.AddPatron(); break;
            case 2:
                std::cout << "Enter ID of patron to edit: ";
                std::cin >> id;
                patrons.EditPatron(id);
                break;
            case 3: patrons.FindPatron(); break;
            case 4: patrons.PrintAllPatrons(); break;
            case 5: patrons.PrintPatronsWithFines(); break;
            case 6:
                std::cout << "Enter ID of patron paying fines: ";
                std::cin >> id;
                patrons.PayFines(id);
                break;
            default: std::cout << "Invalid choice.\n";
        }
    }
}

void handleLoansMenu(Loans& loans, Patrons& patrons, LibraryItems& library) {
    int choice;
    while(true) {
        std::cout << "\n--- Loan Management ---\n"
                  << "1. Check Out Item\n"
                  << "2. Check In Item\n"
                  << "3. List All Loans\n"
                  << "4. List Overdue Loans\n"
                  << "5. List Loans for a Patron\n"
                  << "6. Return to Main Menu\n"
                  << "Option: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (choice == 6) break;

        int patronID, itemID, loanID;
        switch (choice) {
            case 1: 
                std::cout << "Enter Patron ID: ";
                std::cin >> patronID;
                std::cout << "Enter Item ID to check out: ";
                std::cin >> itemID;
                loans.CheckOutItem(patronID, itemID, patrons, library);
                break;
            case 2:
                std::cout << "Enter Loan ID to check in: ";
                std::cin >> loanID;
                loans.CheckInItem(loanID, patrons, library);
                break;
            case 3: loans.PrintAllLoans(); break;
            case 4: loans.ListOverdueLoans(); break;
            case 5:
                std::cout << "Enter Patron ID to list their loans: ";
                std::cin >> patronID;
                loans.AllLoansForPatron(patronID);
                break;
            default: std::cout << "Invalid choice.\n";
        }
    }
}