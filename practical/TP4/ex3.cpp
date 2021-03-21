#include "exercises.h"

bool changeMakingDP(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    unsigned int error = T+1;
    unsigned int minCoins[n+1][T+1];
    unsigned int lastCoin[n+1][T+1];
    unsigned int Stock2[n];

    for (int i = 0; i < n; ++i) {
        Stock2[i] = Stock[i];
    }

    for (unsigned int i = 0; i < n+1; ++i) {
        for (unsigned int k = 0; k <= T; ++k) {

            if (k == 0) {
                minCoins[i][k] = 0;
            }
            else if (k > 0 && i == 0) {
                minCoins[i][k] = error;
            } else {
                int a = valid(i, 0, k, C[i-1]) ? minCoins[i][k-C[i-1]] + 1 : error;
                int b = valid(i, 1, k, 0) ? minCoins[i-1][k] : error;

                minCoins[i][k] = std::min(a,b);
            }


            if (k == 0 || (k > 0 && i == 0))
                lastCoin[i][k] = 0;
            else {
                int a = valid(i, 0, k, C[i-1]) && Stock2[i-1] ? minCoins[i][k-C[i-1]] + 1 : error;
                int b = valid(i, 1, k, 0) ? minCoins[i-1][k] : error;

                if (a < b && C[i-1] <= k) {
                    lastCoin[i][k] = C[i-1];
                }
                else {
                    lastCoin[i][k] = lastCoin[i-1][k];
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        usedCoins[i] = 0;
    }



    // Backtracking
    unsigned int i = -1;

    unsigned int value = T;

    size_t maxCoin = n;
    for (i = T; i > 0;) {
        if (i == 0 || maxCoin == 0) break;
        size_t idx = getCoinIdx(C, maxCoin, lastCoin[maxCoin][i]);
        if (idx == -1) {
            return false;
        }
        else if (Stock[idx] <= 0) {
            maxCoin--;
            continue;
        }
        usedCoins[idx]++;
        Stock[idx]--;
        i -= lastCoin[maxCoin][i];
        maxCoin = n;
    }


    return i == 0;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex3, hasChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingDP(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingDP(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingDP(C,Stock3,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP4_Ex3, hasChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingDP(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingDP(C,Stock2,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C,Stock2,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP4_Ex3, hasNoChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingDP(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingDP(C,Stock,n,1,usedCoins), false);
}