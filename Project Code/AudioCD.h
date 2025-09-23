#ifndef AUDIOCDH
#define AUDIOCDH

#include "LibraryItem.h"
#include <iostream>
#include <string>
using namespace std;

class AudioCD : public LibraryItem {
private:
    string artist;
    string title;
    int numOfTracks;
    string releaseDate;
    string genre;

    public:
    AudioCD();

    // Setters
    void SetArtist(const string& artistName);
    void SetTitle(const string& cdTitle);
    void SetNumOfTracks(int numTracks);
    void SetReleaseDate(const string& date);
    void SetGenre(const string& cdGenre);

    // Getters
    string GetArtist() const;
    string GetTitle() const;
    int GetNumOfTracks() const;
    string GetReleaseDate() const;
    string GetGenre() const;

    // Polymorphic overrides
    string GetItemType() const override;
    void InputDetails() override;
    void EditDetails() override;
    void PrintHeader(ostream& os) const override;
    void PrintDetails(ostream& os) const override;
    bool Matches(int criteria, const string& value) const override;
    string serialize() const override;
    bool deserialize(istream& inFile) override;
};

#endif