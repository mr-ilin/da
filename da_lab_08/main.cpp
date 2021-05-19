#include <iostream>
#include "coins.h"

int main() {
    std::ios_base::sync_with_stdio(false);

    long long coinsCount, coinValue, toExchange;
    std::cin >> coinsCount >> coinValue >> toExchange;

    std::vector<long long> result = NGreedyCoins::minCoinCharge(coinsCount, coinValue, toExchange);
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << result[i] << std::endl;
    }
    return 0;
}
