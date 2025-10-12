#include "LibraryItem.h"
#include <string>
#include <algorithm> // For std::transform
#include <stdexcept>

void LibraryItem::SetLibraryID(int iD) {
    this->libraryID = iD;
}

void LibraryItem::SetCost(double itemCost) {
    this->cost = itemCost;
}

void LibraryItem::SetStatus(const std::string& newStatus) {
    this->status = newStatus;
}

void LibraryItem::SetLoanPeriod(int prd) {
    this->loanPeriod = prd;
}

int LibraryItem::GetLibraryID() const {
    return libraryID;
}

double LibraryItem::GetCost() const {
    return cost;
}

std::string LibraryItem::GetStatus() const {
    return status;
}

int LibraryItem::GetLoanPeriod() const {
    return loanPeriod;
}

void LibraryItem::InputDetails() {
    // Default implementation can be empty or provide a base prompt
}

void LibraryItem::EditDetails() {
    // Default implementation can be empty or provide a base prompt
}

// Base implementation for common search criteria
bool LibraryItem::Matches(int criteria, const std::string& value) const {
    try {
        switch (criteria) {
            case 1: { // Status
                std::string itemStatus = status;
                std::string searchStatus = value;
                std::transform(itemStatus.begin(), itemStatus.end(), itemStatus.begin(), 
                    [](unsigned char c){ return std::tolower(c); });
                std::transform(searchStatus.begin(), searchStatus.end(), searchStatus.begin(), 
                    [](unsigned char c){ return std::tolower(c); });
                return itemStatus == searchStatus;
            }
            case 2: { // Library ID
                return libraryID == std::stoi(value);
            }
            case 3: { // Loan Period
                return loanPeriod == std::stoi(value);
            }
            default:
                return false;
        }
    } catch (const std::invalid_argument&) {
        // Handle cases where stoi fails (e.g., non-numeric input for ID)
        return false;
    }
}