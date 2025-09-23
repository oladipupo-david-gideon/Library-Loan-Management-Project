#ifndef LIBRARYITEMS
#define LIBRARYITEMS

#include "Book.h"
#include "AudioCD.h"
#include "DVD.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <memory> // Optional if you want to use smart pointers

using namespace std;

class LibraryItems {
private:
    vector<LibraryItem*> items;
    LibraryItem* CreateItemFromType(const string& type);

public:
    ~LibraryItems(); // Destructor to delete pointers

    vector<LibraryItem*>& GetLibraryItems();

    int GenerateUniqueID();

    // Book-specific ID generation
    long GenerateUniqueISBN();

    void AddItem();
    void EditItem(int libraryID);
    void DeleteItem(int libraryID);
    void FindItem(); // Based on item type + criteria
    void PrintAllItems();
    void PrintItem(int libraryID);

    // Persistence
    void EnsureFileExists(const string& filename);
    void saveToFile();
    void loadFromFile();

};

#endif
