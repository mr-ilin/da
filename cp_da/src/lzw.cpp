#include "lzw.h"

namespace NAlgo {

    void TLZW::InitDict(std::unordered_map<std::string, size_t>& dict) {
        dict.clear();
        dict = {
                {"a", 0},
                {"b", 1},
                {"c", 2},
                {"d", 3},
                {"e", 4},
                {"f", 5},
                {"g", 6},
                {"h", 7},
                {"i", 8},
                {"j", 9},
                {"k", 10},
                {"l", 11},
                {"m", 12},
                {"n", 13},
                {"o", 14},
                {"p", 15},
                {"q", 16},
                {"r", 17},
                {"s", 18},
                {"t", 19},
                {"u", 20},
                {"v", 21},
                {"w", 22},
                {"x", 23},
                {"y", 24},
                {"z", 25}
        };
        // a b c d e f g h i j k l m n o p q r s t u v w x y z
    }

    void TLZW::InitDict(std::vector<std::string>& dict) {
        dict.clear();
        dict = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    }

    std::vector<size_t> TLZW::Encode(const std::string& text) {
        std::unordered_map<std::string, size_t> dict;
        InitDict(dict);

        std::vector<size_t> result;
        std::string str;
        for (char ch : text) {
            auto search = dict.find(str + ch);
            if (search != dict.end()) {
                str += ch;
            } else {
                result.emplace_back(dict[str]);
                dict[str + ch] = dict.size();
                str = ch;
            }
        }
        if (str.size()) {
            result.emplace_back(dict[str]);
        }

        return result;
    }

    std::string TLZW::Decode(const std::vector<size_t>& codes) {
        std::vector<std::string> dict;
        InitDict(dict);

        size_t prevCode = codes.front();
        if (prevCode >= dict.size()) {
            throw std::runtime_error("Invalid code");
        }
        std::string entry, result;
        entry = result = dict[prevCode];

        for (auto it = std::begin(codes) + 1; it != std::end(codes); ++it) {
            size_t currCode = *it;
            if (currCode < dict.size()) {
                entry = dict[currCode];
            } else if (currCode == dict.size()){
                entry += entry[0]; // ?
            } else {
                throw std::runtime_error("Invalid code");
            }

            result += entry;
            dict.push_back(dict[prevCode] + entry[0]);
            prevCode = currCode;
        }

        return result;
    }
} // namespace NAlgo