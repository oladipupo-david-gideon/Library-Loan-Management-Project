#ifndef AUDIO_CD_H
#define AUDIO_CD_H

#include "LibraryItem.h"
#include <string>
#include <iostream>

class AudioCD : public LibraryItem {
private:
    std::string artist;
    std::string title;
    int numOfTracks;
    std::string releaseDate;
    std::string genre;

public:
    AudioCD();

    // Setters
    void SetArtist(const std::string& artistName);
    void SetTitle(const std::string& cdTitle);
    void SetNumOfTracks(int numTracks);
    void SetReleaseDate(const std::string& date);
    void SetGenre(const std::string& cdGenre);

    // Getters
    std::string GetArtist() const;
    std::string GetTitle() const;
    int GetNumOfTracks() const;
    std::string GetReleaseDate() const;
    std::string GetGenre() const;

    // Polymorphic overrides
    std::string GetItemType() const override;
    void InputDetails() override;
    void EditDetails() override;
    void PrintHeader(std::ostream& os) const override;
    void PrintDetails(std::ostream& os) const override;

    std::string serialize() const override;
    bool deserialize(std::istream& inFile) override;
};

#endif