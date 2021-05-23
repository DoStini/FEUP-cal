#include "exercises.h"

#include <vector>
#include <fstream>

void computePattern(const std::string & pattern, std::vector<int> & buffer) {
    int size = pattern.size();

    buffer = std::vector<int>(size);

    int j = 0;
    for (int i = 1; i < size; ++i) {
        while (j > 0 && pattern.at(j) != pattern.at(i))
            j = buffer[j-1];

        if (pattern.at(j) == pattern.at(i))
            j++;
        buffer[i] = j;
    }
}

int kmpMatcher(std::string text, std::string pattern) {
    std::vector<int> buf;

    computePattern(pattern, buf);

    int tSize = text.size();
    int pSize = pattern.size();

    int numMatches = 0;

    int j = 0;

    for (int i = 0; i < tSize; ++i) {
        while (j > 0 && pattern.at(j) != text.at(i))
            j = buf.at(j-1);
        if (pattern.at(j) == text.at(i))
            j++;
        if (j == pattern.size()) {
            numMatches++;
            j = buf.at(j-1);
        }
    }
    return numMatches;
}

int numStringMatching(std::string filename, std::string toSearch) {
    std::ifstream in(filename);

    std::string text;
    std::string temp;

    while (getline(in, temp))
        text += "\n" + temp;

    return kmpMatcher(text, toSearch);
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP10_Ex1, testKmpMatcher) {
    EXPECT_EQ(3, kmpMatcher("aaabaabaacaabaa", "aabaa"));

    EXPECT_EQ(0, kmpMatcher("", "a"));
    EXPECT_EQ(1, kmpMatcher("a", "a"));
}

#define REL_PATH std::string("../TP10/") // relative path to the tests

TEST(TP10_Ex1, testNumStringMatching) {
    int num1 = numStringMatching(REL_PATH + "text1.txt", "estrutura de dados");
    EXPECT_EQ(3, num1);

    int num2=numStringMatching(REL_PATH +"text2.txt", "estrutura de dados");
    EXPECT_EQ(2,num2);
}