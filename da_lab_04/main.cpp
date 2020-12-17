#include <iostream>
#include "kmp.hpp"

bool isSpace(char c) {
    return ((c == ' ') || (c == '\t') || (c == '\n'));
}

enum TState {
    inStr,
    betweenStrs
};

int main(int argc, const char * argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::vector<std::vector<std::string>> text;
    std::vector<std::string> pattern;
    
    bool firstLine = true;
    TState state = betweenStrs;
    std::vector<std::string> currentLine;
    std::string currentStr;
    
    char letter = getchar();
    while (letter != EOF) {
        switch (state) {
            case betweenStrs:
                if (!isSpace(letter)) {
                    state = inStr;
                    break;
                }
                
                if (letter == '\n') {
                    if (firstLine) {
                        pattern = std::move(currentLine); // Перемещает текущую строку в образец
                        firstLine = false;
                    } else {
                        text.push_back(std::move(currentLine)); // Добавляем текущую строку в конец
                    }
                    currentLine.clear();
                }
                letter = getchar();
                break;
                
            case inStr:
                if (isSpace(letter)) {
                    currentLine.push_back(std::move(currentStr)); // Перемещаем текущее слово в текущую строку
                    currentStr.clear();
                    state = betweenStrs;
                    break;
                }
                currentStr.push_back(std::tolower(letter));
                letter = getchar();
                break;
        }
    }
    
    KMPSearch(text, pattern);
    
    return 0;
}
