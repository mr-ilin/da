#include <iostream>
#include "kmp.hpp"

bool isSpaceCh(char c) {
    return ((c == ' ') || (c == '\t') || (c == '\n'));
}

int main(int argc, const char * argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::vector<std::vector<std::string>> text;
    std::vector<std::string> pattern;
    
    char c;
    bool patternLine = true;
    std::vector<std::string> currentLine;
    std::string currentStr;
    do {
        c = getchar(); // Считываем текущий символ
        
        // Если пропался пробельный символ
        if (isSpaceCh(c)) {
            // Проверка на пустую строчку
            if (currentLine.empty() && currentStr.empty() && c == '\n') {
                continue;
            }
            
            currentLine.push_back(std::move(currentStr)); // Перемещаем текущее слово в текущую строку
            currentStr.clear();
            
            // Если конец строки
            if (c == '\n') {
                if (patternLine) {
                    pattern = std::move(currentLine); // Перемещает текущую строку в образец
                    patternLine = false;
                } else {
                    text.push_back(std::move(currentLine)); // Добавляем текущую строку в конец
                }
                currentLine.clear();
            }
            
            continue;
        }
        
        currentStr.push_back(std::tolower(c));
    } while (c != EOF);
    
    std::cout << "PATTERN = \" \n";
    for (auto word : pattern) {
        std::cout << word << " ";
    }
    std::cout << "\" \n";
    
    std::cout << "TEXT = \" \n";
    for (auto line : text) {
        for (auto word : line) {
            std::cout << word << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\" \n";
    
    //KMPSearch(text, pattern);
    
    return 0;
}
