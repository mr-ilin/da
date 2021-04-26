#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <gtest/gtest.h>
#include "dp.hpp"

std::stringstream logError(std::vector<std::vector<int> > expected, std::vector<std::vector<int> > result) {
    std::stringstream resultStream;
    for (auto col : expected) {
        for (auto num : col) {
            resultStream << std::to_string(num) << " ";
        }
        resultStream << "\n";
    }
    resultStream << " != ";
    for (auto col : result) {
        for (auto num : col) {
            resultStream << std::to_string(num) << " ";
        }
        resultStream << "\n";
    }
    return resultStream;
}

TEST(TDPMatrixSuite, areasTest) {

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
        }
    };

    std::vector < std::vector< std::vector<int> > > expectedMatrixs {
        // 1
        {
            {1}
        },
        // 2
        {
            {1, 2}
        },
        // 3
        {
            {1, 2},
            {2, 0}
        },
        // 4
        {
            {1, 0, 1, 0, 0}, 
            {0, 1, 2, 3, 0},
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
            {1, 2},
            {2, 4},
            {3, 6}
        },
        // 7
        {
            {0, 0, 0, 0, 0, 0, 1, 2},
            {0, 0, 0, 0, 0, 0, 2, 4},
            {0, 0, 0, 0, 0, 0, 3, 6},
            {1, 2, 3, 4, 5, 6, 7, 8}
        },
        // 8
        {
            {0, 0, 1, 0},
            {0, 0, 2, 0},
            {0, 0, 3, 0},
            {0, 1, 4, 3},
            {0, 2, 5, 6},
            {0, 3, 6, 9}
        },
        // 9
        {
            {0, 0, 0, 1},
            {0, 0, 0, 2},
            {0, 0, 1, 3},
            {0, 0, 2, 4},
            {0, 0, 3, 6},
            {0, 1, 4, 8},
            {0, 2, 5, 10},
            {1, 3, 6, 12},
        }
    };

    for (size_t i = 0; i < values.size(); ++i) {
        std::vector<std::string> value = values[i];
        std::vector<std::vector<int> > expected = expectedMatrixs[i];
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