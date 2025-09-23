# Makefile for Library Management System project

# Define object files
OBJ_FILES = main.o Book.o AudioCD.o DVD.o Patron.o Patrons.o Loan.o Loans.o LibraryItem.o LibraryItems.o

# Default target to build the executable
main: $(OBJ_FILES)
	g++ -o main $(OBJ_FILES)

# Compilation rules for object files
main.o: main.cpp LibraryClock.h Book.h AudioCD.h DVD.h Patron.h Patrons.h Loan.h Loans.h LibraryItem.h LibraryItems.h
	g++ -c main.cpp

Book.o: Book.cpp Book.h
	g++ -c Book.cpp

AudioCD.o: AudioCD.cpp AudioCD.h
	g++ -c AudioCD.cpp

DVD.o: DVD.cpp DVD.h
	g++ -c DVD.cpp

Patron.o: Patron.cpp Patron.h
	g++ -c Patron.cpp

Patrons.o: Patrons.cpp Patrons.h
	g++ -c Patrons.cpp

Loan.o: Loan.cpp Loan.h
	g++ -c Loan.cpp

Loans.o: Loans.cpp Loans.h
	g++ -c Loans.cpp

LibraryItem.o: LibraryItem.cpp LibraryItem.h
	g++ -c LibraryItem.cpp

LibraryItems.o: LibraryItems.cpp LibraryItems.h
	g++ -c LibraryItems.cpp

# Release target (non-debug build)
release: $(OBJ_FILES)
	g++ -o main $(OBJ_FILES)

# Debug target (with debugging symbols)
debug: $(OBJ_FILES)
	g++ -Wall -DDEBUG -o main $(OBJ_FILES)

# Cross-platform clean rule
clean:
ifeq ($(OS),Windows_NT)
	@cmd /C "del /Q main.exe *.o 2>nul || exit 0"
else
	@rm -f main main.exe *.o
endif
