CXX=g++
CXXFLAGS=-I ./ -std=c++20 -g -O3 -fsanitize=address
WARNINGS=-Wall
EXEC=server_requests

all: run

$(EXEC): main.cpp server_requests.cpp testcases/one.cpp testcases/two.cpp testcases/three.cpp testcases/four.cpp testcases/five.cpp testcases/six.cpp testcases/seven.cpp
	$(CXX) $(CXXFLAGS) $(WARNINGS) $^ -o $@

run: $(EXEC)
	./$(EXEC)

clean:
	rm -rf $(EXEC) *.o *.dSYM
	rm -rf *~
