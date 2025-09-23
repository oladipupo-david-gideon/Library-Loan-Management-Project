#include "LibraryItems.h"
#include "Book.h"
#include "DVD.h"
#include "AudioCD.h"

#include <iostream>
#include <sstream>
#include <random>
#include <iomanip>
#include <algorithm>
#include <regex>
#include <fstream>
#include <cctype>

using namespace std;

// Return all library items as a reference (to modify the actual collection)
vector<LibraryItem*>& LibraryItems::GetLibraryItems() {
    return items;
}

// Destructor to clean up dynamically allocated memory
LibraryItems::~LibraryItems() {
    for (LibraryItem* item : items) {
        delete item;
    }
    items.clear();
}

// Generate a unique 6-digit ID
int LibraryItems::GenerateUniqueID() {
    static vector<int> usedIDs;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(100000, 999999);

    int id;
    do {
        id = dist(gen);
    } while (find(usedIDs.begin(), usedIDs.end(), id) != usedIDs.end());

    usedIDs.push_back(id);
    return id;
}

// Generate a unique 9-digit ISBN
long LibraryItems::GenerateUniqueISBN() {
    static vector<long> usedISBNs;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long> dist(100000000L, 999999999L);

    long isbn;
    do {
        isbn = dist(gen);
    } while (find(usedISBNs.begin(), usedISBNs.end(), isbn) != usedISBNs.end());

    usedISBNs.push_back(isbn);
    return isbn;
}

// Add an item based on user input
void LibraryItems::AddItem() {
    int choice;
    cout << "Select item type to add:\n1. Book\n2. DVD\n3. Audio CD\nChoice: ";
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number (1-3).\n";
        return;
    }
    cin.ignore();

    LibraryItem* newItem = nullptr;

    switch (choice) {
        case 1: {
            Book* book = new Book();
            book->InputDetails();
            book->SetLibraryID(GenerateUniqueID());
            book->SetISBN(GenerateUniqueISBN());
            book->SetLoanPeriod(14);
            book->SetStatus("In");
            newItem = book;
            break;
        }
        case 2:
            newItem = new DVD();
            newItem->InputDetails();
            newItem->SetLibraryID(GenerateUniqueID());
            newItem->SetLoanPeriod(14);
            newItem->SetStatus("In");
            break;
        case 3:
            newItem = new AudioCD();
            newItem->InputDetails();
            newItem->SetLibraryID(GenerateUniqueID());
            newItem->SetLoanPeriod(14);
            newItem->SetStatus("In");
            break;
        default:
            cout << "Invalid choice.\n";
            return;
    }

    items.push_back(newItem);
    cout << "Item added successfully.\n";
}

// Edit item by ID
void LibraryItems::EditItem(int libraryID) {
    if (libraryID <= 0) {
        cout << "Invalid ID. Please enter a positive number.\n";
        return;
    }

    for (auto& item : items) {
        if (item->GetLibraryID() == libraryID) {
            cout << "Editing item:\n";
            item->EditDetails();
            cout << "Item updated successfully.\n";
            return;
        }
    }
    cout << "Item not found.\n";
}

// Delete item by ID
void LibraryItems::DeleteItem(int libraryID) {
    if (libraryID <= 0) {
        cout << "Invalid ID. Please enter a positive number.\n";
        return;
    }

    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->GetLibraryID() == libraryID) {
            delete *it;
            items.erase(it);
            cout << "Item deleted.\n";
            return;
        }
    }
    cout << "Item not found.\n";
}

// Find item(s) by type and criteria
void LibraryItems::FindItem() {
    if (items.empty()) {
        cout << "No items in the library to search.\n";
        return;
    }

    int itemChoice;
    cout << "Select item type to search:\n";
    cout << "1. Book\n2. Audio CD\n3. DVD\nChoice: ";
    if (!(cin >> itemChoice) || itemChoice < 1 || itemChoice > 3) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid item type.\n";
        return;
    }

    int criteria;
    cout << "Select search criteria:\n";
    cout << "1. Status\n2. Library ID\n3. Loan Period\nChoice: ";
    if (!(cin >> criteria) || criteria < 1 || criteria > 3) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid search criteria.\n";
        return;
    }
    cin.ignore();

    bool found = false;

    for (const auto& item : items) {
        string type = item->GetItemType();
        bool typeMatch =
            (itemChoice == 1 && type == "Book") ||
            (itemChoice == 2 && type == "AudioCD") ||
            (itemChoice == 3 && type == "DVD");

        if (!typeMatch)
            continue;

        switch (criteria) {
            case 1: {
                string status;
                cout << "Enter status (In, Out, Lost): ";
                getline(cin, status);
                transform(status.begin(), status.end(), status.begin(), ::tolower);

                string itemStatus = item->GetStatus();
                transform(itemStatus.begin(), itemStatus.end(), itemStatus.begin(), ::tolower);

                if (status == itemStatus) {
                    item->PrintDetails(cout);
                    found = true;
                }
                break;
            }
            case 2: {
                int id;
                cout << "Enter Library ID: ";
                if (!(cin >> id)) {
                    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid Library ID.\n";
                    return;
                }
                if (item->GetLibraryID() == id) {
                    item->PrintDetails(cout);
                    found = true;
                }
                break;
            }
            case 3: {
                int loanPeriod;
                cout << "Enter Loan Period (in days): ";
                if (!(cin >> loanPeriod)) {
                    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid Loan Period.\n";
                    return;
                }
                if (item->GetLoanPeriod() == loanPeriod) {
                    item->PrintDetails(cout);
                    found = true;
                }
                break;
            }
        }
    }

    if (!found) {
        cout << "No matching items found.\n";
    }
}

// Print all items
void LibraryItems::PrintAllItems() {
    if (items.empty()) {
        cout << "No items to display.\n";
        return;
    }

    // ---- BOOKS ----
    bool headerPrinted = false;
    for (const auto& item : items) {
        if (item->GetItemType() == "Book") {
            if (!headerPrinted) {
                static_cast<const Book*>(item)->PrintHeader(cout);
                headerPrinted = true;
            }
            item->PrintDetails(cout);
        }
    }
    if (headerPrinted) {
        cout << endl << endl;
    }

    // ---- AUDIOCD ----
    headerPrinted = false;
    for (const auto& item : items) {
        if (item->GetItemType() == "AudioCD") {
            if (!headerPrinted) {
                static_cast<const AudioCD*>(item)->PrintHeader(cout);
                headerPrinted = true;
            }
            item->PrintDetails(cout);
        }
    }
    if (headerPrinted) {
        cout << endl << endl;
    }

    // ---- DVD ----
    headerPrinted = false;
    for (const auto& item : items) {
        if (item->GetItemType() == "DVD") {
            if (!headerPrinted) {
                static_cast<const DVD*>(item)->PrintHeader(cout);
                headerPrinted = true;
            }
            item->PrintDetails(cout);
        }
    }
    if (headerPrinted) {
        cout << endl << endl;
    }
}

// Print a specific item by Library ID
void LibraryItems::PrintItem(int libraryID) {
    if (libraryID <= 0) {
        cout << "Invalid Library ID.\n";
        return;
    }

    for (auto item : items) {
        if (item->GetLibraryID() == libraryID) {
            item->PrintHeader(cout);
            item->PrintDetails(cout);
            return;
        }
    }
    cout << "Item not found.\n";
}

// Save all items to file
void LibraryItems::saveToFile() {
    ofstream outFile("items.txt", ios::trunc);
    if (!outFile.is_open()) {
        cerr << "Error: Could not open items.txt for writing!\n";
        return;
    }

    for (const auto& item : items) {
        // Write the type first then a pipe, followed by the serialized data.
        string type = item->GetItemType();  // "Book", "DVD", "AudioCD"
        outFile << type << "|" << item->serialize() << endl;
    }
    outFile.close();
}

// Ensure file exists
void LibraryItems::EnsureFileExists(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.good()) {
        ofstream outFile(filename);
        outFile.close();
    }
}

// Load all items from file
void LibraryItems::loadFromFile() {
    EnsureFileExists("items.txt");
    ifstream inFile("items.txt");
    if (!inFile) {
        cerr << "Failed to open items.txt for reading.\n";
        return;
    }
    
    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue; // skip empty lines
        
        stringstream ss(line);
        string typeToken;
        if (!getline(ss, typeToken, '|')) {
            cerr << "Corrupt line: " << line << endl;
            continue;
        }

        LibraryItem* item = nullptr;
        if (typeToken == "Book")
            item = new Book();
        else if (typeToken == "AudioCD")
            item = new AudioCD();
        else if (typeToken == "DVD")
            item = new DVD();
        else {
            cerr << "Unknown item type in file: " << typeToken << endl;
            continue;
        }

        if (item->deserialize(ss)) {
            items.push_back(item);
        } else {
            cerr << "Failed to deserialize " << typeToken << " item.\n";
            delete item;
        }
    }
    inFile.close();
}
