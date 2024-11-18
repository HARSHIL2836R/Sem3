# Makefile
SHELL := /bin/bash

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17

# Source files
SOURCES = check-tree.cpp grader.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable
EXEC = grader

# Default target
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executable (Unix-like commands)
clean:
	rm -f $(OBJECTS) $(EXEC)
	rm -f *~
