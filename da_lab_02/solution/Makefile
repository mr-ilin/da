CXX=g++
CXXFLAGS=-std=c++17 -pedantic -Wall
EXECUTABLE=solution
SRC=main.cpp avl.cpp string.cpp
OBJ=$(SRC:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

# benchmark: benchmark.o sort.o date.o
# 	$(CC) $(FLAGS) sort.o date.o benchmark.o -o $@

# benchmark.o: benchmark.cpp vector.hpp
# 	$(CC) $(CFLAGS) -c $< -o $@

avl.cpp: avl.hpp

string.cpp : string.hpp

main.o : string.hpp avl.hpp

clean:
	rm -f *.o $(EXECUTABLE)