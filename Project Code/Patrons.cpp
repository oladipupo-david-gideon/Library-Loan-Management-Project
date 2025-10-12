#include "Patrons.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <vector>
#include <limits>

std::vector<Patron>& Patrons::GetPatronList() { 
    return patronList; 
}

int Patrons::GenerateUniquePatronID(){
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(1000000, 9999999);
    
    int id;
    bool isUnique;
    do {
        id = dist(gen);
        isUnique = true;
        for (const auto& patron : patronList) {
            if (patron.GetPatronID() == id) {
                isUnique = false;
                break;
            }
        }
    } while (!isUnique);
    return id;
}

void Patrons::AddPatron() {
    std::string patronName;
    std::cout << "Enter the Patron's name: ";
    std::getline(std::cin, patronName);

    if (patronName.empty()) {
        std::cout << "Error: Patron name cannot be empty." << std::endl;
        return;
    }

    Patron newPatron;
    newPatron.SetPatronName(patronName);
    newPatron.SetPatronID(GenerateUniquePatronID());
    
    patronList.push_back(newPatron);
    std::cout << "Patron '" << patronName << "' added with ID " << newPatron.GetPatronID() << "." << std::endl;
}

void Patrons::EditPatron(int patronID) {
    auto it = std::find_if(patronList.begin(), patronList.end(),
        [patronID](const Patron& p){ return p.GetPatronID() == patronID; });

    if (it == patronList.end()) {
        std::cout << "Patron with ID " << patronID << " not found.\n";
        return;
    }

    int choice;
    bool done = false;
    while (!done) {
        std::cout << "\nEditing Patron: " << it->GetPatronName() << "\n";
        std::cout << "1. Edit Name\n2. Adjust Fine Balance\n3. Done\nChoice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                std::string newName;
                std::cout << "Enter new name: ";
                std::getline(std::cin, newName);
                it->SetPatronName(newName);
                break;
            }
            case 2: {
                double amount;
                std::cout << "Enter amount to adjust fine by (can be negative): ";
                std::cin >> amount;
                it->AdjustFineBalance(amount);
                break;
            }
            case 3:
                done = true;
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
    }
}

void Patrons::DeletePatron(int patronID){
    auto it = std::remove_if(patronList.begin(), patronList.end(), 
        [patronID](const Patron& p) { return p.GetPatronID() == patronID; });

    if (it != patronList.end()) {
        patronList.erase(it, patronList.end());
        std::cout << "Patron with ID " << patronID << " has been deleted." << std::endl;
    } else {
        std::cout << "Patron with ID " << patronID << " not found." << std::endl;
    }
}

void Patrons::FindPatron(){
    std::cout << "Search by:\n1. ID\n2. Name\nChoice: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    bool found = false;
    if (choice == 1) {
        int id;
        std::cout << "Enter ID: ";
        std::cin >> id;
        PrintPatron(id);
    } else if (choice == 2) {
        std::string name;
        std::cout << "Enter name to search for: ";
        std::getline(std::cin, name);
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        
        for (const auto& patron : patronList) {
            std::string patronName = patron.GetPatronName();
            std::transform(patronName.begin(), patronName.end(), patronName.begin(), ::tolower);
            if (patronName.find(name) != std::string::npos) {
                if (!found) {
                     std::cout << std::left << std::setw(12) << "Patron ID" << std::setw(30) << "Patron Name" << std::endl;
                     std::cout << std::string(42, '-') << std::endl;
                }
                std::cout << std::left << std::setw(12) << patron.GetPatronID() << std::setw(30) << patron.GetPatronName() << std::endl;
                found = true;
            }
        }
        if (!found) std::cout << "No patron found with that name.\n";
    }
}

void Patrons::PrintAllPatrons(){
    if (patronList.empty()) {
        std::cout << "There are no patrons in the system." << std::endl;
        return;
    }
    std::cout << "\n--- ALL PATRONS ---\n";
    std::cout << std::left << std::setw(12) << "Patron ID"
              << std::setw(30) << "Patron Name"
              << std::setw(15) << "Fine Balance"
              << std::setw(15) << "Items Out" << std::endl;
    std::cout << std::string(72, '-') << std::endl;
    
    for (const auto& patron : patronList) {
        std::cout << std::left << std::setw(12) << patron.GetPatronID()
                  << std::setw(30) << patron.GetPatronName()
                  << "$" << std::setw(14) << std::fixed << std::setprecision(2) << patron.GetFineBalance()
                  << std::setw(15) << patron.GetItemsOut() << std::endl;
    }
}

void Patrons::PrintPatron(int patronID){
    auto it = std::find_if(patronList.begin(), patronList.end(),
        [patronID](const Patron& p){ return p.GetPatronID() == patronID; });

    if (it != patronList.end()) {
        std::cout << "\n--- Patron Details ---\n";
        std::cout << "ID: " << it->GetPatronID() << "\n";
        std::cout << "Name: " << it->GetPatronName() << "\n";
        std::cout << "Fine Balance: $" << std::fixed << std::setprecision(2) << it->GetFineBalance() << "\n";
        std::cout << "Items Out: " << it->GetItemsOut() << "\n";
    } else {
        std::cout << "Patron with ID " << patronID << " not found.\n";
    }
}

void Patrons::PrintPatronsWithFines() {
    bool found = false;
    for (const auto& patron : patronList) {
        if (patron.GetFineBalance() > 0) {
            if (!found) {
                std::cout << "\n--- PATRONS WITH FINES ---\n";
                std::cout << std::left << std::setw(12) << "Patron ID" << std::setw(30) << "Name" << std::setw(15) << "Fine Balance" << std::endl;
                std::cout << std::string(57, '-') << std::endl;
                found = true;
            }
            std::cout << std::left << std::setw(12) << patron.GetPatronID()
                      << std::setw(30) << patron.GetPatronName()
                      << "$" << std::fixed << std::setprecision(2) << patron.GetFineBalance() << std::endl;
        }
    }
    if (!found) {
        std::cout << "No patrons have outstanding fines.\n";
    }
}

void Patrons::PayFines(int patronID){
    auto it = std::find_if(patronList.begin(), patronList.end(),
        [patronID](const Patron& p){ return p.GetPatronID() == patronID; });
    if (it == patronList.end()) {
        std::cout << "Patron not found.\n";
        return;
    }
    if (it->GetFineBalance() <= 0) {
        std::cout << "Patron has no outstanding fines.\n";
        return;
    }

    double payment;
    std::cout << "Current fine balance is $" << std::fixed << std::setprecision(2) << it->GetFineBalance() << ". Enter payment amount: ";
    std::cin >> payment;
    if (payment < 0) {
        std::cout << "Cannot accept negative payment.\n";
        return;
    }
    if (payment > it->GetFineBalance()) {
        std::cout << "Payment exceeds balance. Paying fine in full.\n";
        it->SetFineBalance(0);
    } else {
        it->AdjustFineBalance(-payment);
    }
    std::cout << "New balance: $" << std::fixed << std::setprecision(2) << it->GetFineBalance() << std::endl;
}

void Patrons::saveToFile() {
    std::ofstream outFile("patrons.txt");
    if (!outFile) {
        std::cerr << "Error opening patrons.txt for writing." << std::endl;
        return;
    }
    for (const auto& patron : patronList) {
        outFile << patron.serialize() << std::endl;
    }
}

void Patrons::loadFromFile() {
    std::ifstream inFile("patrons.txt");
    if (!inFile) {
        return;
    }
    Patron tempPatron;
    while (tempPatron.deserialize(inFile)) {
        patronList.push_back(tempPatron);
    }
}