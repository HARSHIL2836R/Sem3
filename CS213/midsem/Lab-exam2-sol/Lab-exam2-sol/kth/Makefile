# Makefile

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Source files
SOURCES = main.cpp kth.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable
EXEC = main

# Default target
all: $(EXEC)
	./main

# Link object files to create the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

# Compile source files to object files
%.o: %.cpp bst.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

generate: main
	python3 generate-testcases.py tmp 1 1000000
	./main tmp

eval:
	# python3 generate-testcases.py tests/test1 1 1
	# python3 generate-testcases.py tests/test2 1 2
	# python3 generate-testcases.py tests/test3 1 3
	# python3 generate-testcases.py tests/test4 1 4
	python3 generate-testcases.py tests/small-10k  1 10000
	python3 generate-testcases.py tests/small-100k 1 100000
	python3 generate-testcases.py tests/small-1m   1 1000000
	python3 generate-testcases.py tests/small-10m  1 10000000

# Clean up object files and executable
clean:
	rm -f $(OBJECTS) $(EXEC)
	rm -rf *~
	rm -rf output.txt
	rm -rf tmp
