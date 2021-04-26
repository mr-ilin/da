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

    std::pair<int, int> TDPMatrix::prolongRect(const dpCell& curr, const int x, const int y) const {
        return std::make_pair(
            std::max(curr.stripeRow, x),
            std::max(curr.stripeCol, y)
        );
    }

    int getRectArea(const std::pair<int, int> & rectangle, const int i, const int j) {
        return (i - rectangle.first + 1) * (j - rectangle.second + 1);
    }

    int TDPMatrix::fillDpMatrix() {
        int result = 0;
        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        for (int i = 0; i < rows; ++i)  {
            for (int j = 0; j < cols; ++j) {
                if (!matrix[i][j]) {
                    dpMatrix[i][j].stripeRow = -1;
                    dpMatrix[i][j].stripeCol = -1;
                    dpMatrix[i][j].rectangle = std::make_pair(-1, -1);
                    dpMatrix[i][j].maxArea = 0;
                } else {
                    // Обновляем макс. полосы по x и y
                    dpMatrix[i][j].stripeRow = i;
                    if (i > 0) {
                        if (matrix[i - 1][j]) {
                            dpMatrix[i][j].stripeRow = dpMatrix[i - 1][j].stripeRow;
                        }
                    }
                    dpMatrix[i][j].stripeCol = j;
                    if (j > 0) {
                        if (matrix[i][j - 1]) {
                            dpMatrix[i][j].stripeCol = dpMatrix[i][j - 1].stripeCol;
                        }
                    }

                    // Обновляем макс. прямоугольник
                    dpMatrix[i][j].rectangle = std::make_pair(i, j);
                    if (i > 0 && j > 0) {
                        if (matrix[i - 1][j - 1]) {
                            // Выбираем из 3-х прямоугольников:
                            // * продленный rectangle
                            // * продленная полоска stripeRow 
                            // * продленная полоска stripeCol

                            // Продлеваем rectangle
                            int prevX = dpMatrix[i - 1][j - 1].rectangle.first;
                            int prevY = dpMatrix[i - 1][j - 1].rectangle.second;
                            dpMatrix[i][j].rectangle = prolongRect(dpMatrix[i][j], prevX, prevY);

                            // Проверяем продленные полосы
                            std::pair<int, int> nextStripeRow = prolongRect(dpMatrix[i][j], dpMatrix[i][j - 1].stripeRow, j - 1);
                            std::pair<int, int> nextStripeCol = prolongRect(dpMatrix[i][j], i - 1, dpMatrix[i - 1][j].stripeCol);
                            std::pair<int, int> maxStripe;
                            if (getRectArea(nextStripeRow, i, j) > getRectArea(nextStripeCol, i, j)) {
                                maxStripe = nextStripeRow;
                            } else {
                                maxStripe = nextStripeCol;
                            }

                            if (getRectArea(maxStripe, i, j) > getRectArea(dpMatrix[i][j].rectangle, i, j)) {
                                dpMatrix[i][j].rectangle.first  = maxStripe.first;
                                dpMatrix[i][j].rectangle.second = maxStripe.second;
                            }
                        }
                    }

                    // Берем макc 
                    dpMatrix[i][j].maxArea = std::max(
                        getRectArea(dpMatrix[i][j].rectangle, i, j),
                        std::max(i - dpMatrix[i][j].stripeRow + 1, j - dpMatrix[i][j].stripeCol + 1)
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