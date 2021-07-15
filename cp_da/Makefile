CXX = g++
CXXFLAGS = -std=c++17 -pedantic -Wall -Wno-unused-variable
LDFLAGS = 

EXECUTABLE = solution
DEBUG_EXE  = debug.out
TEST       = unit_test

EXE_SRC = src/main.cpp src/lzw.cpp
EXE_OBJ = $(EXE_SRC:.cpp=.o)

TEST_SRC = test/unit_tests.cpp src/lzw.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)

all : $(EXECUTABLE)

debug : CXXFLAGS += -g -fsanitize=address -DDEBUG
debug : EXECUTABLE = $(DEBUG_EXE)
debug : $(EXECUTABLE)

test : LD_FLAGS += -lgtest -lgtest_main
test : $(TEST)

$(EXECUTABLE) : $(EXE_OBJ)
	$(CXX) $(CXXFLAGS) $(EXE_OBJ) -o $(EXECUTABLE)

$(TEST) : $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $(TEST_OBJ) -o $(TEST) $(LD_FLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(EXE_OBJ) $(TEST_OBJ) $(EXECUTABLE) $(DEBUG_EXE) $(TEST)