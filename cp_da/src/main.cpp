#include <iostream>
#include <sstream>
#include "lzw.h"

int main() {
    try {
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "compress") {
            std::string text;
            std::cin >> text;
            std::vector<size_t> encodedText =  NAlgo::TLZW::Encode(text);
            for (auto it = std::begin(encodedText); it != std::end(encodedText); ++it) {
                std::cout << *it;
                if (it != std::end(encodedText) - 1) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        } else if (cmd == "decompress") {
            std::vector<size_t> codes;
            size_t code;
            while (std::cin >> code) {
                codes.push_back(code);
            }
            std::cout << NAlgo::TLZW::Decode(codes);
        } else {
            throw std::runtime_error("Invalid command");
        }
    } catch (const std::exception& ex) {
        std::cerr << ex.what();
    }

    return 0;
}
