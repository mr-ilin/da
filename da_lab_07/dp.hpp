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
            int maxArea;        // Макс. площадь 
            int height;         // Высота ряда
            size_t rightBound;  // Крайний левый индекс, который сохр. высоту
            size_t leftBound;
        };

        std::vector<std::vector<char> > matrix;
        std::vector<std::vector<dpCell> > dpMatrix;

        int fillDpMatrix();
};

} // namespace NMyDP