#include "coins.h"
#include <cmath>

namespace NGreedyCoins {
    std::vector<long long> minCoinCharge(const long long coinsCount, const long long coinValue, long long toExchange) {
        std::vector<long long> result(coinsCount, 0);

        for (long long i = coinsCount - 1; i >= 0; --i) {
            long long currCoinValue = pow(coinValue, i);
            if (toExchange < currCoinValue) {
                continue;
            }

            result[i] = toExchange / currCoinValue;
            toExchange -= result[i] * currCoinValue;
            if (toExchange == 0) {
                break;
            }
        }

        return result;
    }
} //namespace NGreedyCoins
