#include <iostream>
#include <cmath>
#include <iomanip>
#include <chrono>
#include "dp_coins.h"
#include "coins.h"

using timeDuration = std::chrono::microseconds;

void GetTime(std::chrono::time_point<std::chrono::system_clock> & timeVar) {
    timeVar = std::chrono::system_clock::now();
}

int64_t CountTime(const std::chrono::time_point<std::chrono::system_clock> & start, const std::chrono::time_point<std::chrono::system_clock> & end) {
    return std::chrono::duration_cast<timeDuration>(end - start).count();
}

int main() {
    std::ios_base::sync_with_stdio(false);

    std::chrono::time_point<std::chrono::system_clock> start, end;
    int64_t greedyTime, dpTime;

    long long coinsCount, coinValue, toExchange;
    std::cin >> coinsCount >> coinValue >> toExchange;
    std::vector<long long> coins (coinsCount);
    for(long long i = 0; i < coinsCount; ++i) {
        coins[i] = pow(coinValue, i);
    }

    GetTime(start);
    std::vector<long long> GreedyResult = NGreedyCoins::minCoinCharge(coinsCount, coinValue, toExchange);
    GetTime(end);
    greedyTime = CountTime(start, end);

    GetTime(start);
    std::vector<long long> dpResult = NDPCoins::minCoinCharge(coins, toExchange);
    GetTime(end);
    dpTime = CountTime(start, end);

    std::cout << std::setw(7) << "Greedy " << std::setw(10) << greedyTime << " us" << std::endl;
    std::cout << std::setw(7) << "Dp " << std::setw(10) << dpTime << " us" << std::endl;

    for (size_t i = 0; i < GreedyResult.size(); ++i) {
        std::cout << GreedyResult[i] << std::endl;
    }

    for (size_t i = 0; i < dpResult.size(); ++i) {
        std::cout << dpResult[i] << std::endl;
    }
    return 0;
}
