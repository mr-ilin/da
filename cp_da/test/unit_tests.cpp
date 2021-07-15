#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "../src/lzw.h"

std::vector< std::pair< std::string, std::vector<size_t> > > encodedText = {
        { // 1
                "abc",
                {0, 1, 2}
        },
        { // 2
                "acagaatagaca",
                {0, 2, 0, 6, 0, 0, 19, 28, 26, 0}
        },
        { // 3
                "acagaatagaga",
                {0, 2, 0, 6, 0, 0, 19, 28, 33}
        },
        { // 4
                "abababa",
                {0, 1, 26, 28}
        },
        { // 5
                "abababac",
                {0, 1, 26, 28, 2}
        }
};

TEST(LZWSuite, encodeTest) {

    for (size_t i = 0; i < encodedText.size(); ++i) {
        const std::string& text = encodedText[i].first;
        std::vector<size_t> expected = encodedText[i].second;
        std::vector<size_t> result = NAlgo::TLZW::Encode(text);

        ASSERT_EQ(expected, result) << "FAILED test #" << i + 1;
    }
}

TEST(LZWSuite, decodeTest) {

    for (size_t i = 0; i < encodedText.size(); ++i) {
        const std::string& expected = encodedText[i].first;
        std::vector<size_t> codes = encodedText[i].second;
        std::string result = NAlgo::TLZW::Decode(codes);

        ASSERT_EQ(expected, result) << "FAILED test #" << i + 1;
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
