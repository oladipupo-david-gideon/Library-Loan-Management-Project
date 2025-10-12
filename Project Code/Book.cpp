#include "Book.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <regex>
#include <string>

// Helper function to truncate strings
static std::string truncate(const std::string& str, size_t width) {
    if (str.length() > width) {
        return str.substr(0, width - 3) + "...";
    }
    return str;
}

Book::Book() {
    authorName = "unknown";
    bookTitle = "unknown";
    isbn = "0000000000000";
    libraryID = 0;
    cost = 0.00;
    status = "In";
    category = "unknown";
    loanPeriod = 14; // Default for books
}

void Book::SetAuthorName(const std::string& name) { this->authorName = name; }
void Book::SetBookTitle(const std::string& title) { this->bookTitle = title; }
void Book::SetISBN(const std::string& isbn_num) { this->isbn = isbn_num; }
void Book::SetBookCategory(const std::string& cat) { this->category = cat; }

std::string Book::GetAuthorName() const { return authorName; }
std::string Book::GetBookTitle() const { return bookTitle; }
std::string Book::GetISBN() const { return isbn; }
std::string Book::GetBookCategory() const { return category; }
std::string Book::GetItemType() const { return "Book"; }

void Book::InputDetails() {
    std::string input;
    std::cout << "Enter the Book's author: ";
    std::getline(std::cin, authorName);

    std::cout << "Enter the Book's title: ";
    std::getline(std::cin, bookTitle);
    
    std::cout << "Enter the Book's category (e.g., Fiction, SciFi): ";
    std::getline(std::cin, category);

    while (true) {
        std::cout << "Enter the Book's cost: ";
        std::getline(std::cin, input);
        if (std::regex_match(input, std::regex(R"(\d{1,7}(\.\d{1,2})?)")) && std::stod(input) >= 0) {
            SetCost(std::stod(input));
            break;
        }
        std::cout << "Invalid cost. Please enter a positive number (e.g., 19.99).\n";
    }
}

void Book::EditDetails() {
    int choice;
    std::string input;
    bool done = false;

    while (!done) {
        std::cout << "\nEditing Book (ID: " << GetLibraryID() << ")\n";
        std::cout << "1. Title\n2. Author\n3. Category\n4. Cost\n5. Status\n6. Done\nChoice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                std::cout << "Enter new title: ";
                std::getline(std::cin, bookTitle);
                break;
            case 2:
                std::cout << "Enter new author: ";
                std::getline(std::cin, authorName);
                break;
            case 3:
                std::cout << "Enter new category: ";
                std::getline(std::cin, category);
                break;
            case 4:
                 while (true) {
                    std::cout << "Enter new cost: ";
                    std::getline(std::cin, input);
                    if (std::regex_match(input, std::regex(R"(\d{1,7}(\.\d{1,2})?)")) && std::stod(input) >= 0) {
                        SetCost(std::stod(input));
                        break;
                    }
                    std::cout << "Invalid cost. Please enter a positive number (e.g., 19.99).\n";
                }
                break;
            case 5:
                std::cout << "Enter new status (In, Out, Lost): ";
                std::getline(std::cin, status);
                break;
            case 6:
                done = true;
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
    }
}

void Book::PrintHeader(std::ostream& os) const {
    os << "\n--- BOOKS ---\n";
    os << std::left 
       << std::setw(10) << "ID"
       << std::setw(32) << "Title"         // 30 text + 2 padding
       << std::setw(27) << "Author"        // 25 text + 2 padding
       << std::setw(17) << "ISBN"          // 15 text + 2 padding
       << std::setw(17) << "Category"      // 15 text + 2 padding
       << std::setw(12) << "Cost"          // 10 text + 2 padding
       << std::setw(10) << "Status" << std::endl;
    os << std::string(125, '-') << std::endl;
}

void Book::PrintDetails(std::ostream& os) const {
    const int titleWidth = 30;
    const int authorWidth = 25;
    const int categoryWidth = 15;

    os << std::left 
       << std::setw(10) << GetLibraryID()
       << std::setw(titleWidth + 2) << truncate(GetBookTitle(), titleWidth)
       << std::setw(authorWidth + 2) << truncate(GetAuthorName(), authorWidth)
       << std::setw(15 + 2) << GetISBN()
       << std::setw(categoryWidth + 2) << truncate(GetBookCategory(), categoryWidth)
       << "$" << std::setw(11) << std::fixed << std::setprecision(2) << GetCost()
       << std::setw(10) << GetStatus() << std::endl;
}


std::string Book::serialize() const {
    std::stringstream ss;
    ss << bookTitle << "|" << authorName << "|" << isbn << "|" << category << "|"
       << libraryID << "|" << cost << "|" << status << "|" << loanPeriod;
    return ss.str();
}

bool Book::deserialize(std::istream& is) {
    std::string tempCost, tempID, tempPeriod;

    if (std::getline(is, bookTitle, '|') &&
        std::getline(is, authorName, '|') &&
        std::getline(is, isbn, '|') &&
        std::getline(is, category, '|') &&
        std::getline(is, tempID, '|') &&
        std::getline(is, tempCost, '|') &&
        std::getline(is, status, '|') &&
        std::getline(is, tempPeriod))
    {
        try {
            libraryID = std::stoi(tempID);
            cost = std::stod(tempCost);
            loanPeriod = std::stoi(tempPeriod);
            return true;
        } catch (const std::exception&) {
            // This can happen if the data is corrupt
            return false;
        }
    }
    return false;
}