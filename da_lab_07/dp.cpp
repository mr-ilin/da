#include "dp.hpp"

#ifdef DEBUG
#include <iomanip>
#endif

namespace NMyDP {

    TDPMatrix::TDPMatrix(size_t rows, size_t cols)
        : matrix(rows, std::vector<char>(cols)), 
        dpMatrix(rows, std::vector<dpCell>(cols))
    {}

    std::istream& operator>>(std::istream &is, TDPMatrix & rhs) {
        size_t rowsCount = rhs.matrix.size();
        size_t colsCount = rhs.matrix[0].size();
        for (size_t i = 0; i < rowsCount; ++i) {
            std::string row;
            is >> row;
            for (size_t j = 0; j < colsCount; ++j) {
                rhs.matrix[i][j] = row[j];
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

    int TDPMatrix::fillDpMatrix() {
        int result = 0;
        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        
        for (int i = 0; i < rows; ++i) {
            
            // Заполняем значениями пред. ряда и обновляем высоту и левую границу для тек. ряда
            size_t currLeftBound = 0;
            for (int j = 0; j < cols; ++j) {
                if (i > 0) {
                    dpMatrix[i][j] = dpMatrix[i - 1][j];
                    dpMatrix[i][j].maxArea = -1;
                } else {
                    dpMatrix[i][j].height = 0;
                    dpMatrix[i][j].leftBound = 0;
                    dpMatrix[i][j].rightBound = cols - 1;
                    dpMatrix[i][j].maxArea = 0;
                }

                if (matrix[i][j] == '0') {
                    ++dpMatrix[i][j].height;
                    dpMatrix[i][j].leftBound = std::max(dpMatrix[i][j].leftBound, currLeftBound);
                } else {
                    dpMatrix[i][j].height = 0;
                    dpMatrix[i][j].leftBound = 0;
                    currLeftBound = j + 1;
                }
            }

            // Обновляем правую границу
            size_t currRightBound = cols - 1;
            for (int j = cols - 1; j >= 0; --j) {
                if (matrix[i][j] == '0') {
                    dpMatrix[i][j].rightBound = std::min(dpMatrix[i][j].rightBound , currRightBound);
                } else {
                    dpMatrix[i][j].rightBound = cols - 1;
                    currRightBound = j - 1;
                }
            }

            // Считаем площади
            for (int j = 0; j < cols; ++j) {
                dpCell& curr = dpMatrix[i][j];
                curr.maxArea = curr.height * (curr.rightBound - curr.leftBound + 1);
                result = std::max(result, curr.maxArea);
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
                std::cout << std::setw(2) << el.height << " (";
                std::cout << std::setw(2) << el.leftBound << ", ";
                std::cout << std::setw(2) << el.rightBound << ") ";
                std::cout << std::setw(2) << el.maxArea << "\t";
            }
            std::cout << std::endl << std::endl;
        }
    #endif

        return result;
    }

} //namespace NMyDP