#include <iostream>
#include <vector>
#include "dp.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);

    size_t rows, cols;
    std::cin >> rows >> cols;
    NMyDP::TDPMatrix matrix(rows, cols);
    std::cin >> matrix;

    std::cout << matrix.findMaxRectangleArea() << std::endl;
    
    return 0;
}
