#include <iostream>
#include "kmp.hpp"

std::vector<size_t> CountPrefixFunction (const std::vector<std::string>& str) {
    size_t n = str.size();
    std::vector<size_t> sp(n);
    sp[0] = 0;
    size_t lastPrefix = 0;
    for (size_t i = 1; i < n; ++i) {
        while ((lastPrefix > 0) && (str[i] != str[lastPrefix])) {
            lastPrefix = sp[lastPrefix-1];
        }
        if (str[i] == str[lastPrefix]) {
            ++lastPrefix;
        }
        sp[i] = lastPrefix;
    }
    return sp;
}

void KMPSearch(const <std::vector<std::string>>& text, const std::vector<std::string>& pattern) {
    std::vector<size_t> patternPrefix = CountPrefixFunction(pattern);
    
    size_t lastPrefix = 0;
    for (size_t i = 0; i < text.size(); ++i) {
        while ((lastPrefix > 0) && (pattern[lastPrefix] != text[i]))
            lastPrefix = patternPrefix[lastPrefix-1];
 
        if (pattern[lastPrefix] == text[i])
            lastPrefix++;
 
        if (lastPrefix == pattern.size()) {
            std::cout << i + 1 - pattern.size() << std::endl;
        }
    }
}
