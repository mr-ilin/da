#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <gtest/gtest.h>
#include "dp.hpp"

std::vector < std::vector<std::string> > values {
    // 1 test
    {
        "0"
    },
    // 2
    {
        "00"
    },
    // 3
    {
        "00",
        "01"
    },
    // 4
    {
        "01011",
        "10001",
        "01000",
        "11011"
    },
    // 5
    {
        "0101010",
        "1010101",
        "0101010",
        "1010101"
    },
    // 6
    {
        "00",
        "00",
        "00"
    },
    // 7
    {
        "11111100",
        "11111100",
        "11111100",
        "00000000"
    },
    // 8
    {
        "1101",
        "1101",
        "1101",
        "1000",
        "1000",
        "1000"
    },
    // 9
    {
        "1110",
        "1110",
        "1100",
        "1100",
        "1100",
        "1000",
        "1000",
        "0000",
    },
    // 10
    {
        "00000",
        "00000",
        "00100",
        "00000",
        "00000",
    },
    // 11
    {
        "11101",
        "11101",
        "11001",
        "11001",
        "11001",
        "10000",
        "10000",
        "00000",
        "10000",
    }
};

std::vector < std::vector< std::vector<int> > > expectedMatrixs {
    // 1
    {
        {1}
    },
    // 2
    {
        {2, 2}
    },
    // 3
    {
        {2, 2},
        {2, 0}
    },
    // 4
    {
        {1, 0, 1, 0, 0}, 
        {0, 3, 2, 3, 0},
        {1, 0, 3, 4, 3},
        {0, 0, 4, 0, 0}
    },
    // 5
    {
        {1, 0, 1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0, 1, 0},
    },
    // 6
    {
        {2, 2},
        {4, 4},
        {6, 6}
    },
    // 7
    {
        {0, 0, 0, 0, 0, 0, 2, 2},
        {0, 0, 0, 0, 0, 0, 4, 4},
        {0, 0, 0, 0, 0, 0, 6, 6},
        {8, 8, 8, 8, 8, 8, 8, 8}
    },
    // 8
    {
        {0, 0, 1, 0},
        {0, 0, 2, 0},
        {0, 0, 3, 0},
        {0, 3, 4, 3},
        {0, 6, 5, 6},
        {0, 9, 6, 9}
    },
    // 9
    {
        {0, 0, 0, 1},
        {0, 0, 0, 2},
        {0, 0, 2, 3},
        {0, 0, 4, 4},
        {0, 0, 6, 5},
        {0, 3, 8, 6},
        {0, 6, 10, 7},
        {4, 9, 12, 8},
    },
    // 10
    {
        { 5,  5,  5,  5,  5  },
        { 10, 10, 10, 10, 10 },
        { 6,  6,  0,  6,  6  },
        { 8,  8,  5,  8,  8  },
        { 10, 10, 10, 10, 10 },
    },
    // 11
    {
        { 0,  0,  0,  1,  0  },
        { 0,  0,  0,  2,  0  },
        { 0,  0,  2,  3,  0  },
        { 0,  0,  4,  4,  0  },
        { 0,  0,  6,  5,  0  },
        { 0,  4,  8,  6,  4  },
        { 0,  8,  10, 7,  8  },
        { 5,  12, 12, 8,  12 },
        { 0,  16, 14, 9,  16 },
    }
};

std::vector<int> expectedAreas {
    1,   // 1 test
    2,   // 2
    2,   // 3
    4,   // 4
    1,   // 5
    6,   // 6
    8,   // 7
    9,   // 8
    12,  // 9
    10,  //10
    16   //11
};

TEST(TDPMatrixSuite, simpleResultTest) {
    std::vector<size_t> rows {
        1, 10, 100, 150, 250, 350, 400, 500
    };
    std::vector<size_t> cols {
        1, 10, 100, 150, 250, 350, 400, 500
    };

    for (size_t rowsCount : rows) {
        for (size_t colsCount : cols) {

            std::vector<char> rowsSymbols {'0', '1'};
            for (char symbol : rowsSymbols) {
                std::string row = "";
                for (size_t i = 0; i < colsCount; ++i) {
                    row += symbol;
                }

                NMyDP::TDPMatrix matrix(rowsCount, colsCount);
                std::stringstream ss;
                for (size_t i = 0; i < rowsCount; ++i) {
                    ss << row << "\n";
                }
                ss >> matrix;

                int expected = 0;
                if (symbol == '0') {
                    expected = rowsCount * colsCount;
                }
                int result = matrix.findMaxRectangleArea();

                ASSERT_EQ(expected, result) << "FAILED test: symbol = \"" << symbol << "\" rows = " << rowsCount << " cols = " << colsCount;
            }

        }
    }
}

TEST(TDPMatrixSuite, maxAreasTest) {
    for (size_t i = 0; i < values.size(); ++i) {
        std::vector<std::string> & value = values[i];
        int expectedArea = expectedAreas[i];
        size_t rows = value.size();
        size_t cols = value[0].size();

        std::stringstream ss;
        for (std::string str : value) {
            ss << str << "\n";
        }
        NMyDP::TDPMatrix matrix(rows, cols);
        ss >> matrix;
        int result = matrix.findMaxRectangleArea();

        ASSERT_EQ(expectedArea, result) << "FAILED test #" << i + 1;
    }
}

TEST(TDPMatrixSuite, maxAreasMatrixTest) {
    for (size_t i = 0; i < values.size(); ++i) {
        std::vector<std::string> & value = values[i];
        std::vector<std::vector<int> > & expected = expectedMatrixs[i];
        size_t rows = expected.size();
        size_t cols = expected[0].size();

        std::stringstream ss;
        for (std::string str : value) {
            ss << str << "\n";
        }
        NMyDP::TDPMatrix matrix(rows, cols);
        ss >> matrix;
        std::vector<std::vector<int> > result = matrix.getAreas();

        ASSERT_EQ(expected, result) << "FAILED test #" << i + 1;
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}