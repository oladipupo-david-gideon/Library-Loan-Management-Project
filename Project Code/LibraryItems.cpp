#include "LibraryItems.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include <vector>
#include <limits>

std::vector<std::unique_ptr<LibraryItem>>& LibraryItems::GetLibraryItems() {
    return items;
}

int LibraryItems::GenerateUniqueID() {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(100000, 999999);
    int id;
    bool isUnique;
    do {
        id = dist(gen);
        isUnique = true;
        for (const auto& item : items) {
            if (item->GetLibraryID() == id) {
                isUnique = false;
                break;
            }
        }
    } while (!isUnique);
    return id;
}

long long LibraryItems::GenerateUniqueISBN() {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<long long> dist(1000000000000L, 9999999999999L);
    return dist(gen);
}

void LibraryItems::AddItem() {
    int choice;
    std::cout << "Select item type to add:\n1. Book\n2. DVD\n3. Audio CD\nChoice: ";
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input.\n";
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::unique_ptr<LibraryItem> newItem = nullptr;

    switch (choice) {
        case 1: newItem = std::make_unique<Book>(); break;
        case 2: newItem = std::make_unique<DVD>(); break;
        case 3: newItem = std::make_unique<AudioCD>(); break;
        default: std::cout << "Invalid choice.\n"; return;
    }

    newItem->InputDetails();
    newItem->SetLibraryID(GenerateUniqueID());
    if (auto book = dynamic_cast<Book*>(newItem.get())) {
        book->SetISBN(std::to_string(GenerateUniqueISBN()));
    }
    
    items.push_back(std::move(newItem));
    std::cout << "Item added successfully with ID " << items.back()->GetLibraryID() << ".\n";
}

void LibraryItems::EditItem(int libraryID) {
    auto it = std::find_if(items.begin(), items.end(), 
        [libraryID](const auto& item){ return item->GetLibraryID() == libraryID; });
    
    if (it != items.end()) {
        it->get()->EditDetails();
        std::cout << "Item updated.\n";
    } else {
        std::cout << "Item not found.\n";
    }
}

void LibraryItems::DeleteItem(int libraryID) {
    auto it = std::remove_if(items.begin(), items.end(), 
        [libraryID](const std::unique_ptr<LibraryItem>& item) {
            return item->GetLibraryID() == libraryID;
    });

    if (it != items.end()) {
        items.erase(it, items.end());
        std::cout << "Item deleted.\n";
    } else {
        std::cout << "Item not found.\n";
    }
}

void LibraryItems::FindItem() {
    std::cout << "Search by criteria:\n1. Status\n2. Library ID\n3. Loan Period\nChoice: ";
    int criteria;
    std::cin >> criteria;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string value;
    std::cout << "Enter search value: ";
    std::getline(std::cin, value);

    bool found = false;
    for (const auto& item : items) {
        if (item->Matches(criteria, value)) {
            if (!found) {
                std::cout << "\n--- SEARCH RESULTS ---\n";
                item->PrintHeader(std::cout);
                found = true;
            }
            item->PrintDetails(std::cout);
        }
    }

    if (!found) {
        std::cout << "No matching items found.\n";
    }
}

void LibraryItems::PrintAllItems() {
    if (items.empty()) {
        std::cout << "No items in the library.\n";
        return;
    }
    
    bool bookHeader = false, dvdHeader = false, cdHeader = false;

    for (const auto& item : items) {
        if (item->GetItemType() == "Book" && !bookHeader) { item->PrintHeader(std::cout); bookHeader = true; }
    }
    for (const auto& item : items) { if (item->GetItemType() == "Book") item->PrintDetails(std::cout); }
    
    for (const auto& item : items) {
        if (item->GetItemType() == "DVD" && !dvdHeader) { item->PrintHeader(std::cout); dvdHeader = true; }
    }
    for (const auto& item : items) { if (item->GetItemType() == "DVD") item->PrintDetails(std::cout); }
    
    for (const auto& item : items) {
        if (item->GetItemType() == "AudioCD" && !cdHeader) { item->PrintHeader(std::cout); cdHeader = true; }
    }
    for (const auto& item : items) { if (item->GetItemType() == "AudioCD") item->PrintDetails(std::cout); }
}

void LibraryItems::PrintItem(int libraryID) {
    auto it = std::find_if(items.begin(), items.end(), 
        [libraryID](const auto& item){ return item->GetLibraryID() == libraryID; });
    
    if (it != items.end()) {
        it->get()->PrintHeader(std::cout);
        it->get()->PrintDetails(std::cout);
    } else {
        std::cout << "Item not found.\n";
    }
}

void LibraryItems::saveToFile() {
    std::ofstream outFile("items.txt");
    if (!outFile) {
        std::cerr << "Error opening items.txt for writing.\n";
        return;
    }
    for (const auto& item : items) {
        outFile << item->GetItemType() << "|" << item->serialize() << std::endl;
    }
}

void LibraryItems::loadFromFile() {
    std::ifstream inFile("items.txt");
    if (!inFile) {
        return;
    }
    
    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string typeToken;
        if (!std::getline(ss, typeToken, '|')) continue;

        std::unique_ptr<LibraryItem> item = nullptr;
        if (typeToken == "Book") item = std::make_unique<Book>();
        else if (typeToken == "DVD") item = std::make_unique<DVD>();
        else if (typeToken == "AudioCD") item = std::make_unique<AudioCD>();
        else continue;

        if (item->deserialize(ss)) {
            items.push_back(std::move(item));
        }
    }
}