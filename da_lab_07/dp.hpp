#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

namespace NMyDP {  

class TDPMatrix {
    public:
        TDPMatrix(size_t rows, size_t cols);

        int findMaxRectangleArea();
        std::vector<std::vector<int> > getAreas();

        friend std::istream& operator>>(std::istream &is, TDPMatrix & rhs);

    private:

        struct dpCell {
            int maxArea;   // Макс. площадь 
            int stripeRow; // Координата полосы
            int stripeCol;
            std::pair<int, int> rectangle; // Левая верхняя точка прямоугольника
        };

        std::vector<std::vector<bool> > matrix;
        std::vector<std::vector<dpCell> > dpMatrix;

        std::pair<int, int> prolongRect(const dpCell& curr, const int x, const int y) const;
        int fillDpMatrix();
};

} // namespace NMyDP