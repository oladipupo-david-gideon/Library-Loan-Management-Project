
#include "AudioCD.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <regex>
#include <limits>
#include <algorithm>

using namespace std;

// Constructor
AudioCD::AudioCD() {
    this->artist = "unknown";
    this->title = "unknown";
    this->numOfTracks = 0;
    this->releaseDate = "unknown";
    this->genre = "unknown";
    this->libraryID = 0;
    this->cost = 0.00;
    this->status = "none";
    this->loanPeriod = 0;
}

// Setters
void AudioCD::SetArtist(const string& artistName) {
    artist = artistName;
}

void AudioCD::SetTitle(const string& cdTitle) {
    title = cdTitle;
}

void AudioCD::SetNumOfTracks(int numTracks) {
    numOfTracks = numTracks;
}

void AudioCD::SetReleaseDate(const string& date) {
    releaseDate = date;
}

void AudioCD::SetGenre(const string& cdGenre) {
    genre = cdGenre;
}

// Getters
string AudioCD::GetArtist() const {
    return artist;
}

string AudioCD::GetTitle() const {
    return title;
}

int AudioCD::GetNumOfTracks() const {
    return numOfTracks;
}

string AudioCD::GetReleaseDate() const {
    return releaseDate;
}

string AudioCD::GetGenre() const {
    return genre;
}

// Polymorphic overrides
string AudioCD::GetItemType() const {
    return "AudioCD";
}

void AudioCD::InputDetails() {
    cout << "Enter the Artist's Name: ";
    getline(cin, artist);

    cout << "Enter the CD Title: ";
    getline(cin, title);

    cout << "Enter the Genre (Pop, Classic Rock, Classical, Christian, Jazz, New age, etc) : ";
    getline(cin, genre);

    cout << "Enter the Release Date (mm/dd/yyyy): ";
    getline(cin, releaseDate);

    while (true) {
        cout << "Enter the Number of Tracks: ";
        string input;
        getline(cin, input);

        try {
            numOfTracks = stoi(input);
            if (numOfTracks < 0) throw invalid_argument("Negative");
            break;
        } catch (...) {
            cout << "Invalid number. Try again.\n";
        }
    }

    while (true) {
        cout << "Enter the Cost (up to 9 digits with max 2 decimal places): ";
        string input;
        getline(cin, input);
        if (!regex_match(input, regex(R"(\d{1,9}(\.\d{1,2})?)"))) {
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        cost = stod(input);
        if (cost < 0) {
            cout << "Cost cannot be negative. Try again.\n";
            continue;
        }
        break;
    }

    cout << "Audio CD added successfully.\n";
}

void AudioCD::EditDetails() {
    int choice;
    bool doneEditing = false;

    while (!doneEditing) {
        cout << "\nEditing Audio CD with Library ID: " << libraryID << endl;
        cout << "1. Artist\n"
             << "2. Title\n"
             << "3. Genre\n"
             << "4. Release Date\n"
             << "5. Number of Tracks\n"
             << "6. Cost\n"
             << "7. Status\n"
             << "8. Loan Period\n"
             << "9. Done editing\n"
             << "Enter choice: ";

        if (!(cin >> choice) || choice < 1 || choice > 9) {
            cout << "Invalid choice. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(); // clear newline

        switch (choice) {
            case 1: {
                cout << "Enter new Artist Name: ";
                getline(cin, artist);
                cout << "Artist updated.\n";
                break;
            }
            case 2: {
                cout << "Enter new Title: ";
                getline(cin, title);
                cout << "Title updated.\n";
                break;
            }
            case 3: {
                cout << "Enter new Genre: ";
                getline(cin, genre);
                cout << "Genre updated.\n";
                break;
            }
            case 4: {
                cout << "Enter new Release Date (mm/dd/yyyy): ";
                getline(cin, releaseDate);
                cout << "Release Date updated.\n";
                break;
            }
            case 5: {
                string input;
                while (true) {
                    cout << "Enter new Number of Tracks: ";
                    getline(cin, input);
                    try {
                        numOfTracks = stoi(input);
                        if (numOfTracks < 0) throw invalid_argument("Negative");
                        break;
                    } catch (...) {
                        cout << "Invalid input. Try again.\n";
                    }
                }
                cout << "Number of Tracks updated.\n";
                break;
            }
            case 6: {
                string input;
                while (true) {
                    cout << "Enter new Cost: ";
                    getline(cin, input);
                    if (!regex_match(input, regex(R"(\d{1,9}(\.\d{1,2})?)"))) {
                        cout << "Invalid input. Try again.\n";
                        continue;
                    }
                    cost = stod(input);
                    if (cost < 0) {
                        cout << "Cost cannot be negative.\n";
                        continue;
                    }
                    break;
                }
                cout << "Cost updated.\n";
                break;
            }
            case 7: {
                cout << "Enter new Status (In, Out, Lost): ";
                getline(cin, status);
                cout << "Status updated.\n";
                break;
            }
            case 8: {
                string input;
                while (true) {
                    cout << "Enter new Loan Period (days): ";
                    getline(cin, input);
                    try {
                        loanPeriod = stoi(input);
                        if (loanPeriod < 0) throw invalid_argument("Negative");
                        break;
                    } catch (...) {
                        cout << "Invalid loan period. Please enter a non-negative number.\n";
                    }
                }
                cout << "Loan Period updated.\n";
                break;
            }
            case 9:
                doneEditing = true;
                cout << "Finished editing.\n";
                break;
        }
    }
}


void AudioCD::PrintHeader(ostream& os) const {
    os << "AudioCD Details:" << endl << endl;
    os << left << setw(12) << "Genre"
         << setw(20) << "ID"
         << setw(25) << "Artist"
         << setw(25) << "Title"
         << setw(16) << "Release Date"
         << setw(16) << "Tracks"
         << setw(12) << "Cost"
         << setw(20) << "Loan Period(days)"
         << setw(12) << "Status" << endl;

    os << setfill('-') << setw(160) << "-" << endl;
    os << setfill(' ');
}
void AudioCD::PrintDetails(ostream& os) const {
    os << left << setw(12) << genre
         << setw(20) << libraryID
         << setw(25) << artist
         << setw(25) << title
         << setw(16) << releaseDate
         << setw(16) << numOfTracks
         << "$" << setw(11) << fixed << setprecision(2) << cost
         << setw(20) << loanPeriod
         << setw(12) << status << endl;
}

bool AudioCD::Matches(int criteria, const string& value) const {
    switch (criteria) {
        case 1: {
            string cdStatus = status;
            string search = value;
            transform(cdStatus.begin(), cdStatus.end(), cdStatus.begin(), ::tolower);
            transform(search.begin(), search.end(), search.begin(), ::tolower);
            return cdStatus == search;
        }
        case 2:
            return libraryID == stoi(value);
        case 3:
            return loanPeriod == stoi(value);
        default:
            return false;
    }
}

// Serialize
string AudioCD::serialize() const {
    stringstream ss;
    ss << artist << "|" << title << "|" << genre << "|" << releaseDate << "|"
       << numOfTracks << "|" << libraryID << "|" << cost << "|" << status << "|" << loanPeriod;
    return ss.str();
}

// Deserialize
bool AudioCD::deserialize(istream& inFile) {
    string line;
    if (getline(inFile, line)) {
        stringstream ss(line);
        string tempTracks, tempID, tempCost, tempLoan;

        getline(ss, artist, '|');
        getline(ss, title, '|');
        getline(ss, genre, '|');
        getline(ss, releaseDate, '|');
        getline(ss, tempTracks, '|');
        getline(ss, tempID, '|');
        getline(ss, tempCost, '|');
        getline(ss, status, '|');
        getline(ss, tempLoan);

        numOfTracks = stoi(tempTracks);
        libraryID = stoi(tempID);
        cost = stod(tempCost);
        loanPeriod = stoi(tempLoan);

        return true;
    }
    return false;
}
