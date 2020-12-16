CXX=g++
CXXFLAGS=-std=c++17 -pedantic -Wall
EXECUTABLE=solution
SRC=main.cpp avl.cpp string.cpp
OBJ=$(SRC:.cpp=.o)

all: $(EXECUTABLE)

debug: CXXFLAGS += -g -no-pie
debug: all

$(EXECUTABLE): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

benchmark: benchmark.o string.o avl.o
	$(CXX) $(CXXFLAGS) $^ -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

avl.cpp: avl.hpp string.hpp

string.cpp : string.hpp

main.o : string.hpp avl.hpp

clean:
	rm -f *.o $(EXECUTABLE) benchmark
