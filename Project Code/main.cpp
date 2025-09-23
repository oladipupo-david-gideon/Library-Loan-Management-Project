/* Name: David Oladipiupo (DavidOladipupo@my.unt.edu)
Course: CSCE 1040.003
Assignment: Hwk #4
Date Started: 04/15/2025
Date Completed: 04/20/2025
Instructor: Dr. Mosquera
Description: A Libray Loan Program that handles different items loaned from the library
*/

#include "LibraryItems.h"
#include "Patrons.h"
#include "Loans.h"
#include "LibraryClock.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

LibraryItems library;  // Library object to manage items.
Patrons patrons;  // Patrons object to manage patrons.
Loans loans;  // Loans object to manage loans.

void printMainMenu() {
    cout << "\nLibrary Main Menu\n";
    cout << setfill('-') << setw(20) << "-" << endl;
    cout << setfill(' ');
    cout << "1. Items\n";
    cout << "2. Patrons\n";
    cout << "3. Loans\n";
    cout << "4. Exit\n";
    cout << "Please select an option: ";
}

void printLibraryItemMenu() {
    cout << "\nLibrary Item Menu\n";
    cout << setfill('-') << setw(25) << "-" << endl;
    cout << setfill(' ');
    cout << "1. Add Item To Library\n";
    cout << "2. Edit Item In Library\n";
    cout << "3. Delete Item In Library\n";
    cout << "4. Find Item In Library\n";
    cout << "5. Show All Items In Library\n";
    cout << "6. Show An Item Information\n";
    cout << "7. Main Menu\n";
    cout << "8. Exit\n";
    cout << "Please select an option: ";
}

void printPatronMenu() {
    cout << "\nLibrary Patron Menu" << endl;
    cout << setfill('-') << setw(25) << "-" << endl;
    cout << setfill(' ');
    cout << "1. Add Patron\n";
    cout << "2. Edit Patron Informatioin\n";
    cout << "3. Delete Patron\n";
    cout << "4. Search For Patron\n";
    cout << "5. Show All Patrons\n";
    cout << "6. Show A Patron Information\n";
    cout << "7. Show Patrons With Fines\n";
    cout << "8. Pay Patron Fine\n";
    cout << "9. Main Menu\n";
    cout << "10. Exit\n";
    cout << "Please select an option: ";
}

void printLoanMenu() {
    cout << "\nLibrary Loan Menu\n";
    cout << setfill('-') << setw(25) << "-" << endl;
    cout << setfill(' ');
    cout << "1. Check Out Item\n";
    cout << "2. Check In Item\n";
    cout << "3. Re-Check An Item\n";
    cout << "4. Show All Loans\n";
    cout << "5. Show All Loans For Patron\n";
    cout << "6. Show All Overdue Loans\n";
    cout << "7. Show All Overdue Loans For Patron\n";
    cout << "8. Report Lost Item\n";
    cout << "9. Edit Loan Information\n";
    cout << "10. Update Loan Status\n";
    cout << "11. Main Menu\n";
    cout << "12. Exit\n";
    cout << "Please select an option: ";
}

int main() {
    library.loadFromFile();
    patrons.loadFromFile();
    loans.loadFromFile();

    // Call UpdateAllLoans to ensure all loans are up-to-date
    loans.UpdateAllLoans(patrons.GetPatronList());
    


    int mainChoice, subChoice, itemID, patronID, loanID;

    while (true) {
        // Main Menu
        printMainMenu();
        cin >> mainChoice;
        cin.ignore();  // Ignore leftover newline character

        switch (mainChoice) {
            case 1: // Books Menu
                while (true) {
                    printLibraryItemMenu();
                    cin >> subChoice;
                    cin.ignore();

                    switch (subChoice) {
                        case 1:
                            cout << endl;
                            cout << "Adding an item to the library...\n";
                            library.AddItem();
                            break;
                        case 2:
                            cout << endl;
                            cout << "Editing an item in the library...\n";
                            cout << "What is the ID of the item you would like to edit? \n";
                            cin >> itemID;
                            cin.ignore();
                            library.EditItem(itemID);
                            break;
                        case 3:
                            cout << endl;
                            cout << "Deleting an item from the library...\n";
                            cout << "What is the ID of the item you would like to delete? \n";
                            cin >> itemID;
                            cin.ignore();
                            library.DeleteItem(itemID);
                            break;
                        case 4:
                            cout << endl;
                            cout << "Finding an item in the library...\n";
                            library.FindItem();  
                            break;
                        case 5:
                            cout << endl;
                            library.PrintAllItems();  
                            break;
                        case 6:
                            cout << endl;
                            cout << "Showing item information...\n";
                            cout << "What is the ID of the item you would like to view the information of? \n";
                            cin >> itemID;
                            cin.ignore();
                            cout << endl;
                            library.PrintItem(itemID);  
                            break;
                        case 7:
                            cout << endl;
                            cout << "Returning to the main menu...\n";
                            break; // Jump back to the main menu loop
                        case 8:
                            loans.UpdateAllLoans(patrons.GetPatronList());
                            library.saveToFile();
                            patrons.saveToFile();
                            loans.saveToFile();
                            cout << "Exiting program. Goodbye!\n";
                            return 0;
                        default:
                            cout << "Invalid choice, please try again.\n";
                    }
                    if (subChoice == 7) break;  // Exit the loop if needed
                }
                break;

            case 2: // Patrons Menu
                while (true) {
                    printPatronMenu();
                    cin >> subChoice;
                    cin.ignore();

                    switch (subChoice) {
                        case 1:
                            cout << endl;
                            cout << "Adding a patron...\n";
                            patrons.AddPatron();  
                            break;
                        case 2:
                            cout << endl;
                            cout << "Editing patron information...\n";
                            cout << "What is the ID of the patron you would like to edit? \n";
                            cin >> patronID;
                            cin.ignore();
                            cout << endl;
                            patrons.EditPatron(patronID);  
                            break;
                        case 3:
                            cout << endl;
                            cout << "Deleting a patron...\n";
                            cout << "What is the ID of the patron you would like to delete? \n";
                            cin >> patronID;
                            cin.ignore();
                            patrons.DeletePatron(patronID);  
                            break;
                        case 4:
                            cout << endl;
                            cout << "Searching for a patron...\n";
                            patrons.FindPatron();  
                            break;
                        case 5:
                            cout << endl;
                            cout << "Showing all patrons...\n";
                            patrons.PrintAllPatrons();  
                            break;
                        case 6:
                            cout << endl;
                            cout << "Showing patron information...\n";
                            cout << "What is the ID of the patron you would like to view? \n";
                            cin >> patronID;
                            cin.ignore();
                            cout << endl;
                            patrons.PrintPatron(patronID);  
                            break;
                        case 7:
                            cout << endl;
                            cout << "Showing patrons with fines...\n";
                            patrons.PrintPatronsWithFines();  
                            break;
                        case 8:
                            cout << endl;
                            cout << "Paying a patron's fine...\n";
                            cout << "What is the ID of the patron you would like to pay fines for? \n";
                            cin >> patronID;
                            cin.ignore();
                            cout << endl;
                            patrons.PayFines(patronID);  
                            break;
                        case 9:
                            cout << "Returning to the main menu...\n";
                            break; // Jump back to the main menu loop
                        case 10:
                            loans.UpdateAllLoans(patrons.GetPatronList());
                            library.saveToFile();
                            patrons.saveToFile();
                            loans.saveToFile();
                            cout << "Exiting program. Goodbye!\n";
                            return 0;
                        default:
                            cout << "Invalid choice, please try again.\n";
                    }
                    if (subChoice == 9) break;  // Exit the loop if needed
                }
                break;

            case 3: // Loans Menu
                while (true) {
                    printLoanMenu();
                    cin >> subChoice;
                    cin.ignore();
            
                    switch (subChoice) {
                        case 1:
                            cout << endl;
                            cout << "Checking out an item...\n";
                            cout << "What is the ID of the patron you would like to check out for?\n";
                            cin >> patronID;
                            cin.ignore();
                            cout << "What is the ID of the item you would like to check out?\n";
                            cin >> itemID;
                            cin.ignore();
                            loans.CheckOutItem(patronID, itemID, patrons.GetPatronList(), library.GetLibraryItems());  
                            break;
                        case 2:
                            cout << endl;
                            cout << "Checking in an item...\n";
                            cout << "What is the loan ID of the item you would like to check in?\n";
                            cin >> loanID;
                            cin.ignore();
                            loans.CheckInItem(loanID, patrons.GetPatronList(), library.GetLibraryItems());  
                            break;
                        case 3:
                            cout << endl;
                            cout << "Re-checking an item...\n";
                            cout << "What is the loan ID of the item you would like to recheck?\n";
                            cin >> loanID;
                            cin.ignore();
                            loans.ReCheckItem(loanID, patrons.GetPatronList(), library.GetLibraryItems());  
                            break;
                        case 4:
                            cout << endl;
                            loans.PrintAllLoans();  
                            break;
                        case 5:
                            cout << endl;
                            cout << "Showing all loans for a patron...\n";
                            cout << "What is the ID of the patron you would like to view all loans for?\n";
                            cin >> patronID;
                            cin.ignore();
                            loans.AllLoansForPatron(patronID);  
                            break;
                        case 6:
                            cout << endl;
                            cout << "Showing all overdue loans...\n";
                            loans.ListOverdueLoans();  
                            break;
                        case 7:
                            cout << endl;
                            cout << "Showing all overdue loans for a patron...\n";
                            cout << "What is the ID of the patron you would like to view overdue loans for?\n";
                            cin >> patronID;
                            cin.ignore();
                            loans.OverdueLoansForPatron(patronID);  
                            break;
                        case 8:
                            cout << endl;
                            cout << "Reporting a lost item...\n";
                            cout << "What is the loan ID of the item you would like to report as lost?\n";
                            cin >> loanID;
                            cin.ignore();
                            loans.ReportLostItem(loanID, patrons.GetPatronList(), library.GetLibraryItems());  
                            break;
                        case 9:
                            cout << endl;
                            cout << "Editing loan information...\n";
                            cout << "What is the ID of the loan you would like to edit?\n";
                            cin >> loanID;
                            cin.ignore();
                            loans.EditLoan(loanID);  
                            break;
                        case 10:
                            cout << endl;
                            cout << "Updating loan status...\n";
                            cout << "What is the ID of the loan you would like to update its status?\n";
                            cin >> loanID;
                            cin.ignore();
                            loans.UpdateLoanStatus(loanID, patrons.GetPatronList());  
                            break;
                        case 11:
                            cout << "Returning to the main menu...\n";
                            break; // Jump back to the main menu loop
                        case 12:
                            loans.UpdateAllLoans(patrons.GetPatronList());
                            library.saveToFile();
                            patrons.saveToFile();
                            loans.saveToFile();
                            cout << "Exiting program. Goodbye!\n";
                            return 0;
                        default:
                            cout << "Invalid choice, please try again.\n";
                    }
                    if (subChoice == 11) break;  // Exit the loop if needed
                }
                break;

            case 4: // Exit program
                // Call UpdateAllLoans to ensure all loans are up-to-date
                loans.UpdateAllLoans(patrons.GetPatronList());
                library.saveToFile();
                patrons.saveToFile();
                loans.saveToFile();
                cout << "Exiting program. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice, please try again.\n";
                break;
        }
    }

}