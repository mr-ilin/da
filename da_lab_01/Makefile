CC=g++
CFLAGS=-std=c++11 -pedantic -Wall
EXECUTABLE=solution
SRC=main.cpp date.cpp sort.cpp
OBJ=$(SRC:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

benchmark: benchmark.o sort.o date.o
	$(CC) $(FLAGS) sort.o date.o benchmark.o -o $@
	
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

benchmark.o: benchmark.cpp vector.hpp
	$(CC) $(CFLAGS) -c $< -o $@

sort.cpp: sort.hpp
	
date.cpp: date.hpp

main.o: sort.hpp vector.hpp

clean:
	rm -f *.o $(EXECUTABLE)