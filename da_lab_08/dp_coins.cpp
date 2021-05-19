#include <limits>
#include "dp_coins.h"

namespace NDPCoins {
    std::vector<long long> minCoinCharge(const std::vector<long long> & coins, const long long toExchange) {
        std::vector<long long> dp (toExchange + 1, LLONG_MAX);
        std::vector<std::vector<long long> > coinsSet (
                toExchange + 1,
                std::vector<long long> (coins.size(), 0)
                );
        dp[0] = 0;

        for (long long currSum = 0; currSum <= toExchange; ++currSum) {
            for (size_t j = 0; j < coins.size(); ++j) {
                long long coin = coins[j];
                if (coin <= currSum) {
                    if (dp[currSum] >= dp[currSum - coin] + 1) {
                        dp[currSum] = dp[currSum - coin] + 1; // обновляем минимум монет
                        coinsSet[currSum] = coinsSet[currSum - coin]; // изменяем количество монет
                        ++coinsSet[currSum][j];
                    }
                }
            }
        }
        return coinsSet[toExchange];
    }
} // namespace NDPCoins

