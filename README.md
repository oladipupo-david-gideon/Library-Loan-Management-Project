# Library Loan Management System

A console-based library loan management system written in C++. It tracks library items, patrons, and loans, and saves its data to text files so it persists between runs.

This was a class project for a UNT computer science course (CSCE). The repo includes the design document and project report.

> **How it was built:** Built with AI assistance. I led the design, then reviewed and tested the code.

## Features

* Three item types (Books, Audio CDs, and DVDs) that share a common `LibraryItem` base class
* Patrons who can borrow items, with checked-out counts and fine balances
* Loans that connect patrons to items, with due dates
* Overdue tracking and fines, using a library clock to compare due dates to the current date
* Searching and editing for items and patrons, plus paying fines and reporting lost items
* Data saved to and loaded from text files (`items.txt`, `patrons.txt`, `loans.txt`), one record per line

The full list of operations is in the design document (`Design and Report Document/Design Document.pdf`).

## Object-Oriented Design

`LibraryItem` is an abstract base class. `Book`, `AudioCD`, and `DVD` inherit from it and implement its pure virtual functions, such as `GetItemType()`, `PrintHeader()`, `PrintDetails()`, `serialize()`, and `deserialize()`. Other functions (`InputDetails()`, `EditDetails()`, and `Matches()`) are virtual and can be overridden. The program uses these through base-class pointers, so one set of code handles all three item types, and each item type controls how it is saved and loaded.

## Sample Data

The included data files hold sample records for testing: 358 items, 250 loans, and 241 patrons (about 850 records in total).

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
