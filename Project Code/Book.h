#ifndef BOOK_H
#define BOOK_H

#include "LibraryItem.h"
#include <string>
#include <iostream>

class Book : public LibraryItem {
private:
    std::string authorName;
    std::string bookTitle;
    std::string isbn; // Changed to string for robustness
    std::string category;

public:
    Book();

    void SetAuthorName(const std::string& name);
    void SetBookTitle(const std::string& title);
    void SetISBN(const std::string& isbn_num);
    void SetBookCategory(const std::string& cat);

    std::string GetAuthorName() const;
    std::string GetBookTitle() const;
    std::string GetISBN() const;
    std::string GetBookCategory() const;
    std::string GetItemType() const override;

    // Polymorphic functions
    void InputDetails() override;
    void EditDetails() override;
    void PrintHeader(std::ostream& os) const override;
    void PrintDetails(std::ostream& os) const override;

    std::string serialize() const override;
    bool deserialize(std::istream& inFile) override;
};

#endif