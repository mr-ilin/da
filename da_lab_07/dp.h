#pragma once
#include <algorithm>
#include <vector>

namespace NMyDP {  

class TDPMatrix {
    public:
        static int findMaxRectangleArea(const std::vector<std::vector<bool> > & matrix);
    private:
        struct dpNode {
            int maxArea;   // Макс. площадь
            int stripeRow; // Длина полосы до тек. точки
            int stripeCol;
            std::pair<int, int> rectangle; // Левая верхняя точка прямоугольника
        };
};

} // namespace NMyDP