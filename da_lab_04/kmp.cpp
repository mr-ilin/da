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

void KMPSearch(const std::string& text, const std::string& sample) {
    size_t prefix[sample.length()];
     
    size_t last_prefix = prefix[0] = 0;
    for (size_t i=1; i<sample.length(); i++) {
        while (last_prefix > 0 && sample[last_prefix] != sample[i])
            last_prefix = prefix[last_prefix-1];
 
        if (sample[last_prefix] == sample[i])
            last_prefix++;
 
        prefix[i] = last_prefix;
    }
    
    last_prefix = 0;
    for (size_t i=0; i<text.length(); i++) {
        while (last_prefix > 0 && sample[last_prefix] != text[i])
            last_prefix = prefix[last_prefix-1];
 
        if (sample[last_prefix] == text[i])
            last_prefix++;
 
        if (last_prefix == sample.length()) {
            std::cout << i + 1 - sample.length() << std::endl;
        }
    }
}

size_t KMPSearch(const std::vector<std::vector<std::string>>& text, const std::vector<std::string>& pattern) {
    std::vector<size_t> patternPrefix = CountPrefixFunction(pattern);
    size_t occurrances = 0;
    
    size_t lastPrefix = 0;
    for (size_t lineIdx = 0; lineIdx < text.size(); ++lineIdx) {
        for (size_t wordIdx = 0; wordIdx < text[lineIdx].size(); ++wordIdx)
        {
            while ((lastPrefix > 0) && (pattern[lastPrefix] != text[lineIdx][wordIdx])) {
                lastPrefix = patternPrefix[lastPrefix - 1];
            }
                
            if (pattern[lastPrefix] == text[lineIdx][wordIdx]) {
                lastPrefix++;
            }
     
            if (lastPrefix == pattern.size()) {
                --lastPrefix; // tricky???
                ++occurrances;
                
                #ifndef BENCH
                size_t patSize = pattern.size();
                size_t entryLine = lineIdx;
                long long entryWord = wordIdx - (patSize - 1);
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
