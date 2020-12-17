CXX = g++
CXXFLAGS = -std=c++17 -pedantic -Wall -O2

EXECUTABLE = solution
BENCHMARK  = benchmark
SRC = main.cpp kmp.cpp
OBJ = $(SRC:.cpp=.o)

all: $(EXECUTABLE)

debug: CXXFLAGS += -g
debug: $(EXECUTABLE)

benchmark: CXXFLAGS += -D BENCHMARK
benchmark : $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXECUTABLE) benchmark
