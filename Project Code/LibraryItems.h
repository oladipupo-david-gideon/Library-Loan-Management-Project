#ifndef LIBRARYITEMS
#define LIBRARYITEMS

#include "Book.h"
#include "AudioCD.h"
#include "DVD.h"
#include <vector>
#include <string>
#include <memory> // Required for std::unique_ptr

class LibraryItems {
private:
    std::vector<std::unique_ptr<LibraryItem>> items;

public:
    // No longer need a manual destructor, unique_ptr handles it!
    std::vector<std::unique_ptr<LibraryItem>>& GetLibraryItems();

    int GenerateUniqueID();
    long long GenerateUniqueISBN();

    void AddItem();
    void EditItem(int libraryID);
    void DeleteItem(int libraryID);
    void FindItem();
    void PrintAllItems();
    void PrintItem(int libraryID);

    void saveToFile();
    void loadFromFile();
};

#endif