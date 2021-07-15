#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace NAlgo {
    class TLZW {
    public:
        static std::vector<size_t> Encode(const std::string& text);
        static std::string Decode(const std::vector<size_t>& codes);
    private:
        static void InitDict(std::unordered_map<std::string, size_t>& dict);
        static void InitDict(std::vector<std::string>& dict);
    };
} // namespace NAlgo