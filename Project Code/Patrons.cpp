#include "Patrons.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <fstream>
#include <random>
#include <algorithm>

vector<Patron>& Patrons::GetPatronList() { 
    return patronList; 
}
int Patrons::GenerateUniquePatronID(){
    static vector<int> usedIDs; // Stores previously used IDs
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1000000, 9999999); // 7-digit range

    int id;
    do {
        id = dist(gen); // Generate a random 7-digit number
    } while (find(usedIDs.begin(), usedIDs.end(), id) != usedIDs.end()); // Ensure uniqueness

    usedIDs.push_back(id); // Store the new ID
    return id;
}
void Patrons::AddPatron() {
    string patronName;

    cout << "Enter the Patron's name: ";
    getline(cin, patronName);

    // Trim leading/trailing whitespace
    patronName.erase(0, patronName.find_first_not_of(" \t"));
    patronName.erase(patronName.find_last_not_of(" \t") + 1);

    if (patronName.empty()) {
        cout << "Error: Patron name cannot be empty." << endl;
        return;
    }

    Patron newPatron;
    newPatron.SetPatronName(patronName);
    newPatron.SetPatronID(GenerateUniquePatronID());
    newPatron.SetFineBalance(0.00);
    newPatron.SetBooksOut(0);

    patronList.push_back(newPatron);
    cout << "Patron added successfully." << endl;
}
void Patrons::EditPatron(int patronID) {
    auto it = find_if(patronList.begin(), patronList.end(), [patronID](const Patron& p) {
        return p.GetPatronID() == patronID;
    });

    if (it == patronList.end()) {
        cout << "Error: Patron with ID " << patronID << " not found." << endl;
        return;
    }

    Patron& patron = *it;
    bool doneEditing = false;
    const int maxBooksOut = 6;

    while (!doneEditing) {
        cout << "\nEditing Patron (ID: " << patronID << ")\n";
        cout << "1. Edit Name\n2. Edit Fine Balance\n3. Edit Books Checked Out\n4. Done\nChoice: ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        switch (choice) {
            case 1: {
                string newName;
                cout << "Enter new name: ";
                getline(cin, newName);
                if (!newName.empty()) patron.SetPatronName(newName);
                cout << "Name updated successfully." << endl;
                break;
            }
            case 2: {
                double newBalance;
                cout << "Enter new fine balance: ";
                while (!(cin >> newBalance) || newBalance < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid balance. Enter a non-negative number: ";
                }
                patron.SetFineBalance(newBalance);
                cout << "Fine balance updated successfully." << endl;
                break;
            }
            case 3: {
                int newBooks;
                cout << "Enter number of books checked out (max " << maxBooksOut << "): ";
                while (!(cin >> newBooks) || newBooks < 0 || newBooks > maxBooksOut) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid number. Enter a value between 0 and " << maxBooksOut << ": ";
                }
                patron.SetBooksOut(newBooks);
                cout << "Books checked out updated successfully." << endl;
                break;
            }
            case 4:
                doneEditing = true;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}
void Patrons::DeletePatron(int patronID){
    // Find the patron based on the patronID
    auto it = find_if(patronList.begin(), patronList.end(), [patronID](const Patron& p) {
        return p.GetPatronID() == patronID;
    });

    if (it != patronList.end()) {
        patronList.erase(it); // Remove patron from the list
        cout << "Patron with ID " << patronID << " has been deleted." << endl;
    } else {
        cout << "Patron with ID " << patronID << " not found. Deletion not possible." << endl;
    }
}
void Patrons::FindPatron(){//based on criteria
    // Prompt user for search criteria
    int choice;
    cout << "Select search criteria:" << endl;
    cout << "1. Search by Patron Name" << endl;
    cout << "2. Search by PatronID" << endl;
    cout << "3. Search by Fine Balance" << endl;
    cout << "4. Search by Number of Books Checked Out" << endl;
    cout << "Enter your choice (1-4): ";
    cin >> choice;
    cin.ignore(); // To handle the leftover newline character

    bool found = false;
    bool headerPrinted = false;

    switch (choice) {
        case 1: {
            string name;
            cout << "Enter name: ";
            getline(cin, name);
        
            // Convert the entered name to lowercase
            transform(name.begin(), name.end(), name.begin(), ::tolower);
        
            for (const auto& patron : patronList) {
                string patronName = patron.GetPatronName();
        
                // Convert the stored patron name to lowercase
                transform(patronName.begin(), patronName.end(), patronName.begin(), ::tolower);
        
                // Compare the lowercase versions of both names
                if (patronName == name) {
                    patron.DisplayHeader();
                    patron.Display();
                    found = true;
                }
            }
            break;
        }
        case 2: {
            int id;
            cout << "Enter Patron ID: ";
            cin >> id;
            for (const auto& patron : patronList) {
                if (patron.GetPatronID() == id) {
                    patron.DisplayHeader();
                    patron.Display();
                    found = true;
                }
            }
            break;
        }
        case 3: {
            // Search by fine balance
            double balance;
            cout << "Enter fine balance: ";
            cin >> balance;
        
            for (const auto& patron : patronList) {
                if (patron.GetFineBalance() == balance) { 
                    if (!headerPrinted) {
                        // Print the header once
                        patron.DisplayHeader();
                        headerPrinted = true;
                    }
                    patron.Display(); // Display patron info
                    found = true;
                }
            }
            break;
        }
        
        case 4: {
            // Search by number of books checked out
            int books;
            cout << "Enter books checked out: ";
            cin >> books;
        
            for (const auto& patron : patronList) {
                if (patron.GetBooksOut() == books) {
                    if (!headerPrinted) {
                        // Print the header once
                        patron.DisplayHeader();
                        headerPrinted = true;
                    }
                    patron.Display(); // Display patron info
                    found = true;
                }
            }
            break;
        }
        default:
            cout << "Invalid choice." << endl;
    }

    if (!found) {
        cout << "No matching patron found." << endl;
    }
}
void Patrons::PrintAllPatrons(){
    if (patronList.empty()) {
        cout << "There are no patrons currently in the system." << endl;
        return;
    }

    cout << "Displaying all patrons of the library:" << endl << endl;

    cout << left << setw(20) << "Patron ID"
    << setw(35) << "Patron Name" 
    << setw(20) << "Fine Balance"
    << setw(7) << "Number of Books Checked Out" << endl;
    cout << setfill('-') << setw(110) << "-" << endl;
    cout << setfill(' ');

    for (const auto& patron : patronList) {
        patron.Display();
    }
}
void Patrons::PrintPatron(int patronID){
    // Find the patron based on the patronID
    auto it = find_if(patronList.begin(), patronList.end(), [patronID](const Patron& p) {
        return p.GetPatronID() == patronID;
    });

    // If patron is found, print their details
    if (it != patronList.end()) {
        const Patron& patron = *it;
        cout << "Patron Details:" << endl << endl;

        patron.DisplayHeader();
        patron.Display();
    } else {
        cout << "Patron with ID " << patronID << " not found." << endl;
    }
}

void Patrons::PrintPatronsWithFines() {
    bool hasFines = false;

    // First, check if there are any patrons with fines
    for (const auto& patron : patronList) {
        if (patron.GetFineBalance() > 0) {
            hasFines = true;
            break;
        }
    }

    // If no patrons have fines, print a message and return
    if (!hasFines) {
        cout << "No patrons have outstanding fines.\n";
        return;
    }

    // Print header only once
    cout << left << setw(20) << "Patron ID"
    << setw(35) << "Patron Name" 
    << setw(20) << "Fine Balance"
    << setw(7) << "Number of Books Checked Out" << endl;
    cout << setfill('-') << setw(110) << "-" << endl;
    cout << setfill(' ');

    // Now print details for each patron with a fine balance
    for (const auto& patron : patronList) {
        if (patron.GetFineBalance() > 0) {
            patron.Display();
        }
    }
}

void Patrons::PayFines(int patronID){
    for (auto& patron : patronList) {
        if (patron.GetPatronID() == patronID) {
            if (patron.GetFineBalance() > 0) {
                double amount;
                cout << "Patron " << patron.GetPatronName() << " has a fine balance of $" 
                     << patron.GetFineBalance() << "." << endl;
                cout << "Enter amount to pay: $";
                cin >> amount;

                if (amount > patron.GetFineBalance()) {
                    cout << "Overpayment detected! Paying full fine balance of $" 
                    << patron.GetFineBalance() << "." << endl;
                    amount = patron.GetFineBalance();
                }

                patron.SetFineBalance(patron.GetFineBalance() - amount);
                cout << "Payment successful! Remaining balance: $" << patron.GetFineBalance() << endl;
                saveToFile();
                return;
            } else {
                cout << "Patron has no outstanding fines." << endl;
                return;
            }
        }
    }
    cout << "Patron ID not found." << endl;
}

// Save books to a file
void Patrons::saveToFile() {
    ofstream outFile("patrons.txt");
    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }
    for (const auto& patron : patronList) {
        outFile << patron.serialize() << endl;
    }
    outFile.close();
}

void Patrons::EnsureFileExists(const string& filename) {
    // Open file in append mode: creates file if missing, does nothing if it exists
    ofstream outFile(filename, ios::app);  
    outFile.close();  // Close the file immediately without writing
}
// Load books from a file
void Patrons::loadFromFile() {
    EnsureFileExists("patrons.txt");

    ifstream inFile("patrons.txt");
    if (!inFile) {
        cerr << "No saved patrons found." << endl;
        return;
    }
    Patron tempPatron;
    while (tempPatron.deserialize(inFile)) {
        patronList.push_back(tempPatron);
    }
    inFile.close();
}