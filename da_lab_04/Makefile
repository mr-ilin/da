CXX = g++
CXXFLAGS = -std=c++17 -pedantic -Wall -O2

EXECUTABLE = solution
BENCH  = benchmark

EXE_SRC = main.cpp kmp.cpp
EXE_OBJ = $(EXE_SRC:.cpp=.o)

BENCH_SRC = benchmark.cpp kmp.cpp
BENCH_OBJ = $(BENCH_SRC:.cpp=.o)

all: $(EXECUTABLE)

debug : CXXFLAGS += -g
debug : $(EXECUTABLE)

test : CXXFLAGS += -DBENCH
test : $(BENCH)

$(EXECUTABLE) : $(EXE_OBJ)
	$(CXX) $(CXXFLAGS) $(EXE_OBJ) -o $(EXECUTABLE)

$(BENCH) : $(BENCH_OBJ)
	$(CXX) $(CXXFLAGS) $(BENCH_OBJ) -o $(BENCH)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXECUTABLE) $(BENCH)
