#ifndef BOOKH
#define BOOKH

#include "LibraryClock.h"
#include "LibraryItem.h"
#include <string>
using namespace std;
    
class Book : public LibraryItem {
    private:
        string authorName;
        string bookTitle;
        long isbn;
        string category;
    
    public:
        Book();
    
        void SetAuthorName(const string& name);
        void SetBookTitle(const string& title);
        void SetISBN(long isbn_num); // ISBN should be a 10-digit number
        void SetBookCategory(const string& cat);
    
        string GetAuthorName() const;
        string GetBookTitle() const;
        long GetISBN() const;
        string GetBookCategory() const;
        string GetItemType() const override;
    
        // Polymorphic functions
        void InputDetails() override;
        void EditDetails() override;
        void PrintHeader(ostream& os) const override;
        void PrintDetails(std::ostream& os) const override;
        bool Matches(int criteria, const string& value) const override;
    
        string serialize() const override;
        bool deserialize(std::istream& inFile) override;
    };
    
#endif