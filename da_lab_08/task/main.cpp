/*
 * Дан массив неотрицательных целых чисел nums,
 * первоначально Вы находитесь на первом элементе (нулевой индекс).
 * Каждый элемент представляет из себя максимальное количество шагов,
 * на которое вы можете прыгнуть.
 * Вернуть минимальное количество шагов, за которых Вы достигните конца.
 * Можете предполагать, что Вы всегда можете достигнуть конца.
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int jump(vector<int>& nums) {
    int totalJumps = 0;
    int prevMaxJump = 0;
    int maxJump = 0;

    if (nums.size() == 1) {
        return 0;
    }

    for (int i = 0; i < nums.size(); ++i) {
        maxJump = max(
                maxJump,
                i + nums[i] // индекс макс. прыжка с текущей позиции
        );

        if (maxJump >= nums.size() - 1) {
            ++totalJumps;
            break;
        }

        if (i == prevMaxJump) {
            ++totalJumps;
            prevMaxJump = maxJump;
        }
    }
    return totalJumps;
}

int main() {
    vector<vector<int> > input = {
            {1},
            {1, 1},
            {3, 1, 1},
            {1, 3, 1, 1},
            {1, 1, 1},
            {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9}
    };

    for (vector<int>& nums : input) {
        cout <<jump(nums) << endl;
    }
    return 0;
}
