#include <iostream>
#include "kmp.hpp"

std::vector<size_t> CountPrefixFunction (const std::vector<std::string>& str) {
    size_t n = str.size();
    std::vector<size_t> sp(n);
    sp[0] = 0;
    size_t lastPrefix = 0;
    for (size_t i = 1; i < n; ++i) {
        while ((lastPrefix > 0) && (str[i] != str[lastPrefix])) {
            lastPrefix = sp[lastPrefix - 1];
        }
        if (str[i] == str[lastPrefix]) {
            ++lastPrefix;
        }
        sp[i] = lastPrefix;
    }
    return sp;
}

void KMPSearch(const std::vector<std::vector<std::string>>& text, const std::vector<std::string>& pattern) {
    std::vector<size_t> patternPrefix = CountPrefixFunction(pattern);
    
    size_t patSize = pattern.size();
    size_t lastPrefix = 0;
    for (size_t lineIdx = 0; lineIdx < text.size(); ++lineIdx) {
        for (size_t wordIdx = 0; wordIdx < text[lineIdx].size(); ++wordIdx)
        {
            //std::cout << "IN \n text[" << lineIdx << "][" << wordIdx << "]\n";
            while ((lastPrefix > 0) && (pattern[lastPrefix] != text[lineIdx][wordIdx])) {
                //std::cout << "CHECKING \n pattern[" << lastPrefix << "] \n text[" << lineIdx << "][" << wordIdx << "]\n";
                lastPrefix = patternPrefix[lastPrefix - 1];
            }
                
            if (pattern[lastPrefix] == text[lineIdx][wordIdx]) {
                lastPrefix++;
            }
     
            if (lastPrefix == pattern.size()) {
                --lastPrefix;
                size_t entryLine = lineIdx;
                long long entryWord = wordIdx - (patSize - 1);
                while(entryWord < 0) {
                    --entryLine;
                    entryWord += text[entryLine].size();
                }
                //std::cout << lineIdx + 1 - pattern.size() << std::endl;
                std::cout << entryLine + 1 << ", " << entryWord + 1 << std::endl;
            }
        }
    }
}
