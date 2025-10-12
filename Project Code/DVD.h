#ifndef DVD_H
#define DVD_H

#include "LibraryItem.h"
#include <string>
#include <iostream>

class DVD : public LibraryItem {
private:
    std::string title;
    std::string category;
    int runTime;
    std::string studio;
    std::string releaseDate;

public:
    DVD();

    // Setters
    void SetTitle(const std::string& t);
    void SetCategory(const std::string& c);
    void SetRunTime(int rt);
    void SetStudio(const std::string& s);
    void SetReleaseDate(const std::string& rd);

    // Getters
    std::string GetTitle() const;
    std::string GetCategory() const;
    int GetRunTime() const;
    std::string GetStudio() const;
    std::string GetReleaseDate() const;

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