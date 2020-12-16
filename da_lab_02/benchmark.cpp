#include <iostream>
#include <map>
#include <chrono>

#include "string.hpp"
#include "avl.hpp"

using timeDuration = std::chrono::nanoseconds;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    /*
    std::chrono::time_point<std::chrono::system_clock> start, end;
    uint64_t avlTime = 0;
    uint64_t mapTime = 0;

    TAvlTree avl;
    std::map<std::string, uint64_t> map;
    const bool printRes = false;
    
    
    for(uint64_t i = 0; i < 1000000; ++i) {
        std::string str = std::to_string(i);
        TString key(str.c_str());
        uint64_t val(i);
        
        start = std::chrono::system_clock::now();
        map.insert(std::pair<std::string, uint64_t>(str, val));
        end = std::chrono::system_clock::now();
        mapTime += std::chrono::duration_cast<timeDuration>(end - start).count();
        
        start = std::chrono::system_clock::now();
        avl.Insert(std::move(key), std::move(val), printRes);
        end = std::chrono::system_clock::now();
        avlTime += std::chrono::duration_cast<timeDuration>(end - start).count();
    }
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Insert std::map time = " << (double)mapTime/1000000000 << "s" << std::endl;
    std::cout << "Insert avl tree time = " << (double)avlTime/1000000000 << "s" << std::endl;

    avlTime = 0;
    mapTime = 0;

    for (int i = 0; i < 1000000; ++i) {
        start = std::chrono::system_clock::now();
        map.find(std::to_string(999999));
        end = std::chrono::system_clock::now();
        mapTime += std::chrono::duration_cast<timeDuration>(end - start).count();
        
        start = std::chrono::system_clock::now();
        TString key(std::to_string(999999).c_str());
        avl.Find(key);
        end = std::chrono::system_clock::now();
        avlTime += std::chrono::duration_cast<timeDuration>(end - start).count();
    }
    std::cout << std::endl;
    std::cout << "Search std::map time = " << (double)mapTime/1000000000 << "s" << std::endl;
    std::cout << "Search avl tree time = " << (double)avlTime/1000000000 << "s" << std::endl;
    
    avlTime = 0;
    mapTime = 0;

    for (int i = 0; i < 1000000; ++i) {
        start = std::chrono::system_clock::now();
        map.erase(std::to_string(999999-i));
        end = std::chrono::system_clock::now();
        mapTime += std::chrono::duration_cast<timeDuration>(end - start).count();
        
        start = std::chrono::system_clock::now();
        TString key(std::to_string(999999-i).c_str());
        avl.Remove(key, printRes);
        end = std::chrono::system_clock::now();
        avlTime += std::chrono::duration_cast<timeDuration>(end - start).count();
    }
    std::cout << std::endl;
    std::cout << "Delete std::map time = " << (double)mapTime/1000000000 << "s" << std::endl;
    std::cout << "Delete avl tree time = " << (double)avlTime/1000000000 << "s" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    
    
    
    */
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int64_t avlInsertTime = 0;
    int64_t mapInsertTime = 0;
    int64_t avlDeleteTime = 0;
    int64_t mapDeleteTime = 0;
    int64_t avlSearchTime = 0;
    int64_t mapSearchTime = 0;
    int64_t avlSaveTime = 0;
    int64_t avlLoadTime = 0;

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
                uint64_t value2 = value;
                
                start = std::chrono::system_clock::now();
                tree.Insert(std::move(key2), std::move(value2), printResult);
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
                    start = std::chrono::system_clock::now();
                    tree.Save(path, printResult);
                    end = std::chrono::system_clock::now();
                    avlSaveTime += std::chrono::duration_cast<timeDuration>(end - start).count();
                } else {
                    start = std::chrono::system_clock::now();
                    tree.Load(path, printResult);
                    end = std::chrono::system_clock::now();
                    avlLoadTime += std::chrono::duration_cast<timeDuration>(end - start).count();
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
    std::cout << std::endl;
    std::cout << "Save avl tree time = " << avlSaveTime << "ms" << std::endl;
    std::cout << "Load avl tree time = " << avlLoadTime << "ms" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    
    return 0;
}
