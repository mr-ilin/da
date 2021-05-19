#include <vector>
#include <tuple>
#include <gtest/gtest.h>
#include <cmath>

#include "coins.h"
#include "dp_coins.h"

// coinsCount, coinValue, toExchange
std::vector<std::tuple<long long, long long, long long> > canonicalValues = {
        {3, 5, 71},         // 1
        {1, 2, 65},         // 2
        {1, 228, 65},       // 3
        {2, 4, 33},         // 4
        {9, 10, 175},       // 5
        {5, 69, 0},         // 6
        {5, 2, 64}          // 7
};

std::vector<std::vector<long long> > canonicalExpResults = {
        {1, 4, 2},                   // 1
        {65},                        // 2
        {65},                        // 3
        {1, 8},                      // 4
        {5, 7, 1, 0, 0, 0, 0, 0, 0}, // 5
        {0, 0, 0, 0, 0},             // 6
        {0, 0, 0, 0, 4}              // 7
};

std::vector<std::vector<long long> > usualCoins = {
        {25, 20, 10, 5},         // 1
        {9, 6, 5, 1}             // 2
};

std::vector<long long> usualExchange = {
        40, // 1
        11  // 2
};

std::vector<std::vector<long long> > usualExpResults = {
        {0, 2, 0, 0},                // 1
        {0, 1, 1, 0}                 // 2
};

TEST(GreetyCoinsSuite, greetyMinCoinChargeCanonicalTest) {
    for (size_t testIdx = 0; testIdx < canonicalValues.size(); ++testIdx) {
        long long coinsCount, coinValue, toExchange;
        std::tie(coinsCount, coinValue, toExchange) = canonicalValues[testIdx];
        std::vector<long long> result = NGreedyCoins::minCoinCharge(coinsCount, coinValue, toExchange);
        std::vector<long long> & expected = canonicalExpResults[testIdx];

        ASSERT_EQ(expected, result) << "FAILED test #" << testIdx + 1;
    }
}

TEST(DPCoinsSuite, DpMinCoinChargeCanonicalTest) {
    for (size_t testIdx = 0; testIdx < canonicalValues.size(); ++testIdx) {
        long long coinsCount, coinValue, toExchange;
        std::tie(coinsCount, coinValue, toExchange) = canonicalValues[testIdx];

        std::vector<long long> coins (coinsCount);
        for(long long i = 0; i < coinsCount; ++i) {
            coins[i] = pow(coinValue, i);
        }

        std::vector<long long> result = NDPCoins::minCoinCharge(coins, toExchange);
        std::vector<long long> & expected = canonicalExpResults[testIdx];

        ASSERT_EQ(expected, result) << "FAILED test #" << testIdx + 1;
    }
}

TEST(DPCoinsSuite, DpMinCoinChargeUsualTest) {
    for (size_t testIdx = 0; testIdx < usualCoins.size(); ++testIdx) {
        long long toExchange = usualExchange[testIdx];
        const std::vector<long long> & coins = usualCoins[testIdx];

        std::vector<long long> result = NDPCoins::minCoinCharge(coins, toExchange);
        std::vector<long long> & expected = usualExpResults[testIdx];

        ASSERT_EQ(expected, result) << "FAILED test #" << testIdx + 1;
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}