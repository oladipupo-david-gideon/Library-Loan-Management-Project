# Makefile for Library Management System

# Compiler and flags
CXX = g++
# Use C++17 standard, enable all warnings for better code quality
CXXFLAGS = -std=c++17 -Wall -Wextra
# Debug flags
DEBUG_FLAGS = -g -DDEBUG
# Executable name
TARGET = main

# Automatically find all .cpp files in the current directory
SOURCES = $(wildcard *.cpp)
# Generate corresponding .o object file names from the source file names
OBJECTS = $(SOURCES:.cpp=.o)

# Default target: build the release version
all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Generic rule to compile any .cpp file into a .o file
# $< is the first prerequisite (the .cpp file)
# $@ is the target name (the .o file)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Debug target: rebuilds with debug flags
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: clean all

# Clean target: remove executable and object files
clean:
ifeq ($(OS),Windows_NT)
	del /Q $(TARGET) *.o 2>nul || exit 0
else
	rm -f $(TARGET) $(OBJECTS)
endif

# .PHONY tells make that these are command names, not files
.PHONY: all debug clean