#include "dp.hpp"

#ifdef DEBUG
#include <iomanip>
#endif

namespace NMyDP {

    TDPMatrix::TDPMatrix(size_t rows, size_t cols)
        : matrix(rows, std::vector<bool>(cols)), 
        dpMatrix(rows, std::vector<dpCell>(cols))
    {}

    std::istream& operator>>(std::istream &is, TDPMatrix & rhs) {
        size_t rowsCount = rhs.matrix.size();
        size_t colsCount = rhs.matrix[0].size();
        for (size_t i = 0; i < rowsCount; ++i) {
            std::string row;
            is >> row;
            for (size_t j = 0; j < colsCount; ++j) {
                rhs.matrix[i][j] = (row[j] == '0');
            }
        }
        return is;
    }

    int TDPMatrix::findMaxRectangleArea() {
        return fillDpMatrix();
    }

    std::vector<std::vector<int> > TDPMatrix::getAreas() {
        fillDpMatrix();
        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        std::vector<std::vector<int> > result (
            rows, 
            std::vector<int>(cols)
        );

        for (size_t i = 0; i < rows; ++i)  {
            for (size_t j = 0; j < cols; ++j) {
                result[i][j] = dpMatrix[i][j].maxArea;
            }
        }

        return result;
    }

    // std::pair<int, int> prolongRect(const dpCell& curr, const std::pair<int, int> & rect) const {
    //     return std::make_pair(
    //         std::max(i + 1 - stripeRow, prevX),
    //         std::max(j + 1 - stripeCol, prevY)
    //     );
    // }

    int TDPMatrix::fillDpMatrix() {
        int result = 0;
        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        for (int i = 0; i < rows; ++i)  {
            for (int j = 0; j < cols; ++j) {
                if (!matrix[i][j]) {
                    dpMatrix[i][j].stripeRow = 0;
                    dpMatrix[i][j].stripeCol = 0;
                    dpMatrix[i][j].rectangle = std::make_pair(-1, -1);
                    dpMatrix[i][j].maxArea = 0;
                } else {
                    // Обновляем макс. полосы по x и y
                    dpMatrix[i][j].stripeRow = 1;
                    if (i > 0) {
                        dpMatrix[i][j].stripeRow += dpMatrix[i - 1][j].stripeRow ;
                    }
                    dpMatrix[i][j].stripeCol = 1;
                    if (j > 0) {
                        dpMatrix[i][j].stripeCol += dpMatrix[i][j - 1].stripeCol;
                    }

                    // Обновляем макс. прямоугольник
                    dpMatrix[i][j].rectangle = std::make_pair(i, j);
                    if (i > 0 && j > 0) {
                        if (matrix[i - 1][j - 1]) {
                            // Выбираем из 3-х прямоугольников:
                            // * продленный rectangle
                            // * продленная полоска stripeRow 
                            // * продленная полоска stripeCol

                            int stripeRow = dpMatrix[i][j].stripeRow;
                            int stripeCol = dpMatrix[i][j].stripeCol;
                            int prevX = dpMatrix[i - 1][j - 1].rectangle.first;
                            int prevY = dpMatrix[i - 1][j - 1].rectangle.second;

                            dpMatrix[i][j].rectangle.first  = std::max(i + 1 - stripeRow, prevX);
                            dpMatrix[i][j].rectangle.second = std::max(j + 1 - stripeCol, prevY);

                            // ...
                        }
                    }

                    dpMatrix[i][j].maxArea = std::max(
                        (i - dpMatrix[i][j].rectangle.first + 1) * (j - dpMatrix[i][j].rectangle.second + 1),
                        std::max(dpMatrix[i][j].stripeRow, dpMatrix[i][j].stripeCol)
                    );
                    
                    if (dpMatrix[i][j].maxArea > result) {
                        result = dpMatrix[i][j].maxArea;
                    }
                }
            }
        }

    #ifdef DEBUG
        std::cout << "Areas:" << std::endl;
        for (int i = 0; i < rows; ++i)  {
            for (int j = 0; j < cols; ++j) {
                std::cout << "[" << i << "][" << j << "] " <<std::setw(3) << dpMatrix[i][j].maxArea << "\t";
            }
            std::cout << std::endl;
        }

        for (auto row : dpMatrix) {
            for (auto el : row) {
                std::cout << std::setw(2) << el.stripeRow << " & ";
                std::cout << std::setw(2) << el.stripeCol << " (";
                std::cout << std::setw(2) << el.rectangle.first << ", ";
                std::cout << std::setw(2) << el.rectangle.second << ") ";
                std::cout << std::setw(2) << el.maxArea << "\t";
            }
            std::cout << std::endl << std::endl;
        }
    #endif

        return result;
    }

} //namespace NMyDP