#include "DVD.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <regex>
#include <string>
#include <limits>

// Helper function to truncate strings
static std::string truncate(const std::string& str, size_t width) {
    if (str.length() > width) {
        return str.substr(0, width - 3) + "...";
    }
    return str;
}

DVD::DVD() {
    title = "unknown";
    category = "unknown";
    runTime = 0;
    studio = "unknown";
    releaseDate = "unknown";
    libraryID = 0;
    cost = 0.00;
    status = "In";
    loanPeriod = 7; // Default for DVDs
}

void DVD::SetTitle(const std::string& t) { title = t; }
void DVD::SetCategory(const std::string& c) { category = c; }
void DVD::SetRunTime(int rt) { runTime = rt; }
void DVD::SetStudio(const std::string& s) { studio = s; }
void DVD::SetReleaseDate(const std::string& rd) { releaseDate = rd; }

std::string DVD::GetTitle() const { return title; }
std::string DVD::GetCategory() const { return category; }
int DVD::GetRunTime() const { return runTime; }
std::string DVD::GetStudio() const { return studio; }
std::string DVD::GetReleaseDate() const { return releaseDate; }
std::string DVD::GetItemType() const { return "DVD"; }

void DVD::InputDetails() {
    std::string input;
    std::cout << "Enter the DVD Title: ";
    std::getline(std::cin, title);

    std::cout << "Enter the Category (Action, Comedy, etc.): ";
    std::getline(std::cin, category);
    
    std::cout << "Enter the Studio (e.g., Disney, Warner Bros.): ";
    std::getline(std::cin, studio);

    std::cout << "Enter the Release Date (MM/DD/YYYY): ";
    std::getline(std::cin, releaseDate);

    while (true) {
        std::cout << "Enter the Runtime (in minutes): ";
        std::getline(std::cin, input);
        try {
            runTime = std::stoi(input);
            if (runTime >= 0) break;
            else std::cout << "Runtime cannot be negative.\n";
        } catch(const std::exception&) {
            std::cout << "Invalid input. Please enter a whole number.\n";
        }
    }

    while (true) {
        std::cout << "Enter the DVD's cost: ";
        std::getline(std::cin, input);
        if (std::regex_match(input, std::regex(R"(\d{1,7}(\.\d{1,2})?)")) && std::stod(input) >= 0) {
            SetCost(std::stod(input));
            break;
        }
        std::cout << "Invalid cost. Please enter a positive number (e.g., 19.99).\n";
    }
}

void DVD::EditDetails() {
    // Similar menu-based implementation as Book::EditDetails
}

void DVD::PrintHeader(std::ostream& os) const {
    os << "\n--- DVDS ---\n";
    os << std::left 
       << std::setw(10) << "ID"
       << std::setw(32) << "Title"         // 30 text + 2 padding
       << std::setw(22) << "Category"      // 20 text + 2 padding
       << std::setw(22) << "Studio"        // 20 text + 2 padding
       << std::setw(14) << "Runtime"       // 12 text + 2 padding
       << std::setw(12) << "Cost"          // 10 text + 2 padding
       << std::setw(10) << "Status" << std::endl;
    os << std::string(122, '-') << std::endl;
}

void DVD::PrintDetails(std::ostream& os) const {
    const int titleWidth = 30;
    const int categoryWidth = 20;
    const int studioWidth = 20;

    os << std::left 
       << std::setw(10) << libraryID
       << std::setw(titleWidth + 2) << truncate(GetTitle(), titleWidth)
       << std::setw(categoryWidth + 2) << truncate(GetCategory(), categoryWidth)
       << std::setw(studioWidth + 2) << truncate(GetStudio(), studioWidth)
       << std::setw(12 + 2) << std::to_string(runTime) + " min"
       << "$" << std::setw(11) << std::fixed << std::setprecision(2) << cost
       << std::setw(10) << status << std::endl;
}

std::string DVD::serialize() const {
    std::stringstream ss;
    ss << title << "|" << category << "|" << studio << "|" << releaseDate << "|"
       << runTime << "|" << libraryID << "|" << cost << "|" << status << "|" << loanPeriod;
    return ss.str();
}

bool DVD::deserialize(std::istream& is) {
    std::string tempRunTime, tempID, tempCost, tempLoan;
    
    // Parse directly from the stream 'is'
    if (std::getline(is, title, '|') &&
        std::getline(is, category, '|') &&
        std::getline(is, studio, '|') &&
        std::getline(is, releaseDate, '|') &&
        std::getline(is, tempRunTime, '|') &&
        std::getline(is, tempID, '|') &&
        std::getline(is, tempCost, '|') &&
        std::getline(is, status, '|') &&
        std::getline(is, tempLoan))
    {
        try {
            runTime = std::stoi(tempRunTime);
            libraryID = std::stoi(tempID);
            cost = std::stod(tempCost);
            loanPeriod = std::stoi(tempLoan);
            return true;
        } catch(const std::exception&) {
            return false;
        }
    }
    return false;
}