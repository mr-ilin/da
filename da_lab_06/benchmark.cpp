#include "biggest_int.hpp"
#include "gmp.h"

#include <iostream>
#include <vector>
#include <chrono>

using timeDuration = std::chrono::nanoseconds;
const std::string MIN_VALUE = "1";
const std::string MAX_VALUE = "100000000000000000000000000000000000000000000000000000000000000000000000000000000";

int main() {
    std::ios_base::sync_with_stdio(false);

    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::vector<int64_t> myTime;
    std::vector<int64_t> gmpTime;


    
    return 0;
}