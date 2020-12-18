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
    sp.push_back(0);
    return sp;
}

bool EqualToNextPatternWord(const std::vector<std::string>& pattern, const std::string& str, size_t idx) {
    if (idx >= pattern.size()) {
        return false;
    }
    return pattern[idx] == str;
}

size_t KMPSearch(const std::vector<std::vector<std::string>>& text, const std::vector<std::string>& pattern) {
    std::vector<size_t> patternPrefix = CountPrefixFunction(pattern);
    size_t occurrances = 0;
    
    size_t lastPrefix = 0;
    for (size_t lineIdx = 0; lineIdx < text.size(); ++lineIdx) {
        for (size_t wordIdx = 0; wordIdx < text[lineIdx].size(); ++wordIdx)
        {
            while ((lastPrefix > 0) && (!EqualToNextPatternWord(pattern, text[lineIdx][wordIdx], lastPrefix))) {
                lastPrefix = patternPrefix[lastPrefix - 1];
            }
                
            if (pattern[lastPrefix] == text[lineIdx][wordIdx]) {
                lastPrefix++;
            }
     
            if (lastPrefix == pattern.size()) {
                ++occurrances;
                
                #ifndef BENCH
                size_t entryLine = lineIdx;
                long long entryWord = wordIdx - (pattern.size() - 1);
                while(entryWord < 0) {
                    --entryLine;
                    entryWord += text[entryLine].size();
                }
                std::cout << entryLine + 1 << ", " << entryWord + 1 << std::endl;
                #endif
            }
        }
    }
    return occurrances;
}
