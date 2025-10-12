#include "Patron.h"
#include <sstream>

Patron::Patron() {
    patronName = "unknown";
    patronID = 0;
    fineBal = 0.00;
    itemsOut = 0;
}

void Patron::SetPatronName(const std::string& name) { this->patronName = name; }
void Patron::SetPatronID(int id) { this->patronID = id; }
void Patron::SetFineBalance(double bal) { this->fineBal = bal; }
void Patron::SetItemsOut(int numItemsOut) { this->itemsOut = numItemsOut; }

std::string Patron::GetPatronName() const { return patronName; }
int Patron::GetPatronID() const { return patronID; }
double Patron::GetFineBalance() const { return fineBal; }
int Patron::GetItemsOut() const { return itemsOut; }

void Patron::AdjustFineBalance(double amount) { fineBal += amount; }
void Patron::IncrementItemsOut() { itemsOut++; }
void Patron::DecrementItemsOut() { if (itemsOut > 0) itemsOut--; }

std::string Patron::serialize() const {
    std::stringstream ss;
    ss << patronName << "|" << patronID << "|" << fineBal << "|" << itemsOut;
    return ss.str();
}

bool Patron::deserialize(std::istream& inFile) {
    std::string line;
    if (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string tempID, tempFine, tempItems;

        std::getline(ss, patronName, '|');
        std::getline(ss, tempID, '|');
        std::getline(ss, tempFine, '|');
        std::getline(ss, tempItems);

        try {
            patronID = std::stoi(tempID);
            fineBal = std::stod(tempFine);
            itemsOut = std::stoi(tempItems);
        } catch(const std::exception&) {
            return false;
        }
        return true;
    }
    return false;
}