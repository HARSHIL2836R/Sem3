# Makefile
SHELL := /bin/bash

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++20

# Source files
SOURCES = huffman.cpp grader.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable
EXEC = grader

# Link object files to create the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

# Compile source files to object files
%.o: %.cpp huffman.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executable (Unix-like commands)
clean:
	rm -f $(OBJECTS) $(EXEC)
	rm -f *~
