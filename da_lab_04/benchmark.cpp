#include <iostream>
#include <chrono>
#include "kmp.hpp"

using timeDuration = std::chrono::nanoseconds;

std::string RandomString(size_t maxLength) {
    size_t length = rand() % maxLength;
    auto RandChar = []() -> char {
        const char charSet[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const size_t maxIdx = (sizeof(charSet) - 1);
        return charSet[rand() % maxIdx];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, RandChar);
    return str;
}

void RandomLine(size_t maxCount, std::vector<std::string>& strs) {
    std::vector<std::string> result;
    const size_t maxStrLen = 17;
    size_t count = rand() % maxCount;
    for (size_t i = 0; i < count; ++i) {
        strs.push_back(RandomString(maxStrLen));
    }
}

int main(int argc, const char * argv[]) {
    size_t linesCnt = 100000;
//    std::cout << "Enter amount of lines: ";
//    std::cin >> linesCnt;
    
    std::string patternStr = "one two three four4 5fiv5e 9120asD one two three";
    std::vector<std::string> pattern = {
        std::string("one"), std::string("two"), std::string("three"), std::string("four4"),
        std::string("5fiv5e"), std::string("9120asD"), std::string("one"),
        std::string("two"), std::string("three")
    };
    
    std::vector<std::vector<std::string>> text;
    std::string textStr;
    
    const int freq = 5;
    int occurrances = 0;
    for (size_t i = 0; i < linesCnt; ++i) {
        std::vector<std::string> line;
        RandomLine(20, line);
        
        if ((rand() % freq) == 0) {
            ++occurrances;
            size_t idx = 0;
            if (line.size() != 0) {
                idx = rand() % line.size();
            }
            auto it = std::begin(line);
            while(idx > 0) {
                ++it;
                --idx;
            }
            line.insert(it, std::begin(pattern), std::end(pattern));
        }
        
        text.push_back(line);
        for (std::string str : line) {
            textStr += (str + " ");
        }
    }
    std::cout << "TOTAL OCCURRANCES = " << occurrances << std::endl;
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int64_t findTime;
    int64_t kmpTime;
    
    start = std::chrono::system_clock::now();
    size_t pos = textStr.find(patternStr, 0);
    size_t findRes = 0;
    while(pos < textStr.size()) {
        ++findRes;
        pos = textStr.find(patternStr, pos+1);
    }
    end = std::chrono::system_clock::now();
    findTime = std::chrono::duration_cast<timeDuration>(end - start).count();
    
    start = std::chrono::system_clock::now();
    size_t kmpRes = KMPSearch(text, pattern);
    end = std::chrono::system_clock::now();
    kmpTime = std::chrono::duration_cast<timeDuration>(end - start).count();
    
    start = std::chrono::system_clock::now();
    KMPSearch(text, pattern);
    end = std::chrono::system_clock::now();
    int64_t extra = std::chrono::duration_cast<timeDuration>(end - start).count();
    
    std::cout << "===============================" << std::endl;
    std::cout << "  KMP SEARCH RESULT = " << kmpRes << std::endl;
    std::cout << "    KMP SEARCH TIME = " << kmpTime << " ms" << std::endl;
    std::cout << "STRING::FIND RESULT = " << findRes << std::endl;
    std::cout << "  STRING::FIND TIME = " << findTime << " ms" << std::endl;
    std::cout << std::endl;
    std::cout << "KMP ON STD::STRING  = " << extra << " ms" << std::endl;
    std::cout << "===============================" << std::endl;
    
    return 0;
}
