#include <iostream>

#include "string.hpp"
#include "avl.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

    TAvlTree tree;
    TString cmd;
    TString key;
    uint64_t value;
    TString cmd2;
    TString path;
    const bool printResult = true;

    while (std::cin >> cmd) {
        try {
            if (cmd == "+") {
                // Добавление
                std::cin >> key >> value;
                key.ToUpperCase();
                tree.Insert(std::move(key), std::move(value), printResult);
            } else if (cmd == "-") {
                // Удаление
                std::cin >> key;
                key.ToUpperCase();
                tree.Remove(key, printResult);
            } else if (cmd == "!") {
                // Сохранение, загрузка
                std::cin >> cmd2 >> path;
                if (cmd2 == "Save") {
                    tree.Save(path, printResult);
                } else {
                    tree.Load(path, printResult);
                }
            } else if (cmd == "*") {
                // Печать дерева
                tree.Print();
            } else {
                // Поиск
                cmd.ToUpperCase(); // word
                TAvlNode* result = tree.Find(cmd);
                if (!result && printResult) {
                    std::cout << "NoSuchWord\n";
                } else {
                    std::cout << "OK: " << result->value << "\n";
                }
            }
        }
        catch (std::exception& ex) {
            std::cout << "ERROR: " << ex.what() << "\n";
        }
    }
    
    return 0;
}
