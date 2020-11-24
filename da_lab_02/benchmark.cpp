#include <iostream>
#include <map>
#include <chrono>

#include "string.hpp"
#include "avl.hpp"

using timeDuration = std::chrono::microseconds;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int64_t avlInsertTime = 0;
    int64_t mapInsertTime = 0;
    int64_t avlDeleteTime = 0;
    int64_t mapDeleteTime = 0;
    int64_t avlSearchTime = 0;
    int64_t mapSearchTime = 0;

    TAvlTree tree;
    std::map<std::string, uint64_t> map;
    std::string cmd;
    std::string key;
    TString key2;
    uint64_t value;
    TString cmd2;
    TString path;
    const bool printResult = false;

    while (std::cin >> cmd) {
        try {
            if (cmd == "+") {
                std::cin >> key >> value;
                key2 = key.c_str();
                key2.ToUpperCase();
                
                start = std::chrono::system_clock::now();
                tree.Insert(key2, value, printResult);
                end = std::chrono::system_clock::now();
                avlInsertTime += std::chrono::duration_cast<timeDuration>(end - start).count();
                
                start = std::chrono::system_clock::now();
                map.insert(std::pair<std::string, uint64_t>(key, value));
                end = std::chrono::system_clock::now();
                mapInsertTime += std::chrono::duration_cast<timeDuration>(end - start).count();
                
            } else if (cmd == "-") {
                std::cin >> key;
                key2 = key.c_str();
                key2.ToUpperCase();
                
                start = std::chrono::system_clock::now();
                tree.Remove(key2, printResult);
                end = std::chrono::system_clock::now();
                avlDeleteTime += std::chrono::duration_cast<timeDuration>(end - start).count();
                
                start = std::chrono::system_clock::now();
                map.erase(key);
                end = std::chrono::system_clock::now();
                mapDeleteTime += std::chrono::duration_cast<timeDuration>(end - start).count();
                
            } else if (cmd == "!") {
                std::cin >> cmd2 >> path;
                if (cmd2 == "Save") {
                    tree.Save(path, printResult);
                } else {
                    tree.Load(path, printResult);
                }
            } else if (cmd == "*") {
                tree.Print();
            } else {
                key2 = cmd.c_str();
                key2.ToUpperCase();
                
                start = std::chrono::system_clock::now();
                tree.Find(key2);
                end = std::chrono::system_clock::now();
                avlSearchTime += std::chrono::duration_cast<timeDuration>(end - start).count();
                
                start = std::chrono::system_clock::now();
                map.find(cmd);
                end = std::chrono::system_clock::now();
                mapSearchTime += std::chrono::duration_cast<timeDuration>(end - start).count();
            }
        }
        catch (std::exception& ex) {
            std::cout << "ERROR: " << ex.what() << "\n";
        }
    }
    
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Insert std::map time = " << mapInsertTime << "ms" << std::endl;
    std::cout << "Insert avl tree time = " << avlInsertTime << "ms" << std::endl;
    std::cout << std::endl;
    std::cout << "Search std::map time = " << mapSearchTime << "ms" << std::endl;
    std::cout << "Search avl tree time = " << avlSearchTime << "ms" << std::endl;
    std::cout << std::endl;
    std::cout << "Delete std::map time = " << mapDeleteTime << "ms" << std::endl;
    std::cout << "Delete avl tree time = " << avlDeleteTime << "ms" << std::endl;
    std::cout << "-----------------------------" << std::endl;

    return 0;
}
