// By: Gonçalo Leão

#include <algorithm>
#include <numeric>
#include "exercises.h"

std::vector<std::vector<int>> getCombinations(std::vector<int> coins, int idx, int pLvl) {
    std::vector<std::vector<int>> res;
    if(pLvl == 1){
        for (int i = idx; i < coins.size(); ++i) {
            res.push_back({coins[i]});
        }
        return res;
    }
    if(pLvl == coins.size()-idx){
        res.push_back(std::vector<int>());
        for (int i = idx; i < coins.size(); ++i) {
            res[0].push_back(coins[i]);
        }
    }
    if(pLvl > coins.size()-idx)
        return {};

    for (int i = idx; i < coins.size(); ++i) {
        std::vector<std::vector<int>> step = getCombinations(coins, i+1,pLvl-1);
        for (int j = 0; j < step.size(); ++j) {
            step[j].insert(step[j].begin(), coins[i]);
            res.push_back(step[j]);
        }
    }

    return res;
}

bool changeMakingBF(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    std::vector<int> availCoins;
    std::vector<int> chosenCoins;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < Stock[i]; ++j) {
            availCoins.push_back(C[i]);
        }
    }

    bool found = false;

    // Had to put this in the reverse (less brute force) to be more efficiente in the isCanonical function
    for (int i = 0; i < availCoins.size() && !found; ++i) {
        std::vector<std::vector<int>> combs = getCombinations(availCoins, 0, i+1);
        for(const auto & comb: combs){
            if(std::accumulate(comb.begin(), comb.end(), 0) == T){
                chosenCoins = comb;
                found = true;
                break;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        usedCoins[i] = std::count(chosenCoins.begin(),chosenCoins.end(), C[i]);
    }

    return !chosenCoins.empty();
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex3, hasBFChangeCanonical) {
    unsigned int C[] = {1,2,5,10};

    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);
}

TEST(TP1_Ex3, hasBFChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBF(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP1_Ex3, hasNoBFChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingBF(C,Stock,n,1,usedCoins), false);
}