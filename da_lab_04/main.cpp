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
    
    char letter;
    bool firstLine = true;
    std::vector<std::string> currentLine;
    std::string currentStr;
    
    while ((letter = getchar()) != EOF) {
        // Если пропался пробельный символ
        if (isSpaceCh(letter)) {
            // Проверка на пустую строчку
            // if (currentLine.empty() && currentStr.empty() && c == '\n') {
            if (currentLine.empty() && currentStr.empty()) {
                continue;
            }
            
            currentLine.push_back(std::move(currentStr)); // Перемещаем текущее слово в текущую строку
            currentStr.clear();
            
            // Если конец строки
            if (letter == '\n') {
                if (firstLine) {
                    pattern = std::move(currentLine); // Перемещает текущую строку в образец
                    firstLine = false;
                } else {
                    text.push_back(std::move(currentLine)); // Добавляем текущую строку в конец
                }
                currentLine.clear();
            }
            
            continue;
        }
        
        currentStr.push_back(std::tolower(letter));
        letter = getchar();
    }
    
    KMPSearch(text, pattern);
    
    return 0;
}
