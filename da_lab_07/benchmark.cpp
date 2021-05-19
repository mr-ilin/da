#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <chrono>

#include "dp.hpp"

using timeDuration = std::chrono::microseconds;

void GetTime(std::chrono::time_point<std::chrono::system_clock> & timeVar) {
    timeVar = std::chrono::system_clock::now();
}

int64_t CountTime(const std::chrono::time_point<std::chrono::system_clock> & start, const std::chrono::time_point<std::chrono::system_clock> & end) {
    return std::chrono::duration_cast<timeDuration>(end - start).count();
}

int native_algo(const std::vector<std::vector<char> > & matrix) {
    int result = -1;
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // std::cout << "=== in " << i << " " << j << std::endl; //
            if (matrix[i][j] == '0') {
                int currResult = 0;
                for (int rowBound = i; rowBound < rows; ++rowBound) {
                    for (int colBound = j; colBound < cols; ++colBound) {
                        // std::cout << "====== check " << rowBound << " " << colBound << std::endl; //
                        bool isRect = true;
                        for (int x = i; x <= rowBound; ++x) {
                            for (int y = j; y <= colBound; ++y) {
                                if (matrix[i][j] != '0') {
                                    isRect = false;
                                    break;
                                }
                            }
                            if (!isRect) {
                                break;
                            }
                        }

                        if (isRect) {
                            int newRes = (i - rowBound + 1) * (j - colBound + 1);
                            if (newRes > currResult) {
                                currResult = newRes;
                            }
                        }

                    }
                }

                if (currResult > result) {
                    result = currResult;
                }
            }

        }
    }

    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    std::chrono::time_point<std::chrono::system_clock> start, end;
    int64_t dpTime, nativeTime;

    size_t rows, cols;
    std::cin >> rows >> cols;
    std::vector<std::vector<char> > matrix (
        rows, 
        std::vector<char>(cols)
    );
    std::stringstream ss;
    for (size_t i = 0; i < rows; ++i) {
        std::string row;
        std::cin >> row;
        ss << row;
        for (size_t j = 0; j < cols; ++j) {
            matrix[i][j] = row[j];
        }
    }

    NMyDP::TDPMatrix dpMatrix(rows, cols);
    ss >> dpMatrix;


    GetTime(start);
    dpMatrix.findMaxRectangleArea();
    GetTime(end);
    dpTime = CountTime(start, end);

    GetTime(start);
    native_algo(matrix);
    GetTime(end);
    nativeTime = CountTime(start, end);


    std::cout << std::setw(6) << "Dp " << dpTime << std::endl;
    std::cout << std::setw(6) << "Native " << nativeTime << std::endl;

    return 0;
}