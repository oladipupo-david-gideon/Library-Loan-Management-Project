#include "AudioCD.h"
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

AudioCD::AudioCD() {
    artist = "unknown";
    title = "unknown";
    numOfTracks = 0;
    releaseDate = "unknown";
    genre = "unknown";
    libraryID = 0;
    cost = 0.00;
    status = "In";
    loanPeriod = 7; // Default for CDs
}

void AudioCD::SetArtist(const std::string& artistName) { artist = artistName; }
void AudioCD::SetTitle(const std::string& cdTitle) { title = cdTitle; }
void AudioCD::SetNumOfTracks(int numTracks) { numOfTracks = numTracks; }
void AudioCD::SetReleaseDate(const std::string& date) { releaseDate = date; }
void AudioCD::SetGenre(const std::string& cdGenre) { genre = cdGenre; }

std::string AudioCD::GetArtist() const { return artist; }
std::string AudioCD::GetTitle() const { return title; }
int AudioCD::GetNumOfTracks() const { return numOfTracks; }
std::string AudioCD::GetReleaseDate() const { return releaseDate; }
std::string AudioCD::GetGenre() const { return genre; }
std::string AudioCD::GetItemType() const { return "AudioCD"; }

void AudioCD::InputDetails() {
    std::string input;
    std::cout << "Enter the Artist's Name: ";
    std::getline(std::cin, artist);

    std::cout << "Enter the CD Title: ";
    std::getline(std::cin, title);

    std::cout << "Enter the Genre (Pop, Rock, etc.): ";
    std::getline(std::cin, genre);

    std::cout << "Enter the Release Date (MM/DD/YYYY): ";
    std::getline(std::cin, releaseDate);

    while (true) {
        std::cout << "Enter the number of tracks: ";
        std::getline(std::cin, input);
        try {
            numOfTracks = std::stoi(input);
            if (numOfTracks >= 0) break;
            else std::cout << "Number of tracks cannot be negative.\n";
        } catch(const std::exception&) {
            std::cout << "Invalid input. Please enter a whole number.\n";
        }
    }

    while (true) {
        std::cout << "Enter the CD's cost: ";
        std::getline(std::cin, input);
        if (std::regex_match(input, std::regex(R"(\d{1,7}(\.\d{1,2})?)")) && std::stod(input) >= 0) {
            SetCost(std::stod(input));
            break;
        }
        std::cout << "Invalid cost. Please enter a positive number (e.g., 12.99).\n";
    }
}

void AudioCD::EditDetails() {
    // Similar menu-based implementation as Book::EditDetails
}

void AudioCD::PrintHeader(std::ostream& os) const {
    os << "\n--- AUDIO CDS ---\n";
    os << std::left 
       << std::setw(10) << "ID"
       << std::setw(32) << "Title"         // 30 text + 2 padding
       << std::setw(27) << "Artist"        // 25 text + 2 padding
       << std::setw(22) << "Genre"         // 20 text + 2 padding
       << std::setw(12) << "Tracks"        // 10 text + 2 padding
       << std::setw(12) << "Cost"          // 10 text + 2 padding
       << std::setw(10) << "Status" << std::endl;
    os << std::string(125, '-') << std::endl;
}

void AudioCD::PrintDetails(std::ostream& os) const {
    const int titleWidth = 30;
    const int artistWidth = 25;
    const int genreWidth = 20;

    os << std::left 
       << std::setw(10) << libraryID
       << std::setw(titleWidth + 2) << truncate(GetTitle(), titleWidth)
       << std::setw(artistWidth + 2) << truncate(GetArtist(), artistWidth)
       << std::setw(genreWidth + 2) << truncate(GetGenre(), genreWidth)
       << std::setw(10 + 2) << numOfTracks
       << "$" << std::setw(11) << std::fixed << std::setprecision(2) << cost
       << std::setw(10) << status << std::endl;
}

std::string AudioCD::serialize() const {
    std::stringstream ss;
    ss << artist << "|" << title << "|" << genre << "|" << releaseDate << "|"
       << numOfTracks << "|" << libraryID << "|" << cost << "|" << status << "|" << loanPeriod;
    return ss.str();
}

bool AudioCD::deserialize(std::istream& is) {
    std::string tempTracks, tempID, tempCost, tempLoan;

    // Parse directly from the stream 'is'
    if (std::getline(is, artist, '|') &&
        std::getline(is, title, '|') &&
        std::getline(is, genre, '|') &&
        std::getline(is, releaseDate, '|') &&
        std::getline(is, tempTracks, '|') &&
        std::getline(is, tempID, '|') &&
        std::getline(is, tempCost, '|') &&
        std::getline(is, status, '|') &&
        std::getline(is, tempLoan))
    {
        try {
            numOfTracks = std::stoi(tempTracks);
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