#ifndef DVDH
#define DVDH

#include "LibraryItem.h"
#include <iostream>
#include <string>
using namespace std;

class DVD : public LibraryItem {
private:
    string title;
    string category;
    int runTime;
    string studio;
    string releaseDate;

    public:
    DVD();

    // Setters
    void SetTitle(const string& t);
    void SetCategory(const string& c);
    void SetRunTime(int rt);
    void SetStudio(const string& s);
    void SetReleaseDate(const string& rd);

    // Getters
    string GetTitle() const;
    string GetCategory() const;
    int GetRunTime() const;
    string GetStudio() const;
    string GetReleaseDate() const;

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