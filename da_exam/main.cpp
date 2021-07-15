#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;


pair<size_t, size_t> simple_find(vector<size_t>& suff_array, const string& text, const string& pattern) {
    std::pair<vector<size_t>::iterator, vector<size_t>::iterator> range(suff_array.begin(), suff_array.end());
    auto comp = [&text](size_t idx, char value) -> bool {
        return text[idx] < value;
    };

    for (size_t i = 0; i < pattern.size() && range.first != range.second; ++i) {
        range.first = lower_bound(range.first, range.second, pattern[i], comp);
        range.second = upper_bound(range.first, range.second, pattern[i], comp);
    }

    return std::make_pair(*range.first, *range.second);
}


int main() {
    vector<size_t> suff_array = {11, 8, 5, 2, 1, 10, 9, 7, 4, 6, 3};
    string text = "mississippi";

    auto result = simple_find(suff_array, text, "i");
    std::cout << result.first << " " << result.second << std::endl;
    return 0;
}
