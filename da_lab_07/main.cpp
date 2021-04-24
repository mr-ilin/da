#include <iostream>
#include <vector>
#include "dp.h"

int main() {
    std::ios_base::sync_with_stdio(false);

    size_t rowsCount, colsCount;
    std::cin >> rowsCount >> colsCount;
    std::vector<std::vector<bool> > matrix(
        rowsCount,
        std::vector<bool>(colsCount)
    );

    for (size_t i = 0; i < rowsCount; ++i) {
        std::string row;
        std::cin >> row;
        for (size_t j = 0; j < colsCount; ++j) {
            matrix[i][j] = (row[j] == '0');
        }
    }

    std::cout << NMyDP::TDPMatrix::findMaxRectangleArea(matrix) << std::endl;
    
    return 0;
}
