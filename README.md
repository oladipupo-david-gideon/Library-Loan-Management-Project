# Library Loan Management System

A console-based library loan management system written in C++. It tracks library items, patrons, and loans, and saves its data to text files so it persists between runs.

This was a class project for a UNT computer science course (CSCE). The repo includes the design document and project report.

> **How it was built:** Built with AI assistance. I led the design, then reviewed and tested the code.

## Features

* Three item types (Books, Audio CDs, and DVDs) that share a common `LibraryItem` base class
* Menu-driven console interface for managing items, patrons, and loans (see the menus below)
* Loan tracking with overdue loans and patron fine balances
* Data saved to and loaded from text files (`items.txt`, `patrons.txt`, `loans.txt`), one record per line

The design document (`Design and Report Document/Design Document.pdf`) describes the original design of the system.

## Program Menus

**Main menu:** Item Management, Patron Management, Loan Management, Save and Exit

**Item Management:** Add New Item, Delete Item, Edit Item, Find Item, List All Items, List Specific Item

**Patron Management:** Add New Patron, Edit Patron, Find Patron, List All Patrons, List Patrons with Fines, Pay Fines

**Loan Management:** Check Out Item, Check In Item, List All Loans, List Overdue Loans, List Loans for a Patron

Choose **Save and Exit** to write your changes back to the data files.

## Object-Oriented Design

`LibraryItem` is an abstract base class. `Book`, `AudioCD`, and `DVD` inherit from it and implement its pure virtual functions, such as `GetItemType()`, `PrintHeader()`, `PrintDetails()`, `serialize()`, and `deserialize()`. Other functions (`InputDetails()`, `EditDetails()`, and `Matches()`) are virtual and can be overridden. Because `serialize()` and `deserialize()` are virtual, each item type controls how it is saved to and loaded from the data files.

## Sample Data

The included data files hold sample records for testing: 358 items (167 books, 91 DVDs, and 100 audio CDs), 250 loans, and 241 patrons (about 850 records in total). Running the program and choosing **Save and Exit** rewrites these files.

## Project Structure

```
Project Code/                C++ source, Makefile, and the sample data files
Design and Report Document/  Design document (PDF)
Design Document/             Project report
```

## Build and Run

You need a C++ compiler with C++17 support (for example, `g++`).

```bash
cd "Project Code"
g++ -std=c++17 -Wall -Wextra *.cpp -o main
```

Run it from inside the `Project Code` folder so the program can find the data files:

* Windows: `.\main.exe`
* macOS / Linux: `./main`

If you have `make`, the included Makefile does the same build: `make` builds the program, `make debug` builds with debug flags, and `make clean` removes the build files.

## License

MIT. See the `LICENSE` file.
