#include "exercises.h"

bool valid(unsigned int idx, unsigned int subIdx, unsigned int value, unsigned int subVal) {
    return value >= subVal && idx >= subIdx;
}

size_t getCoinIdx(unsigned int C[], unsigned int n, unsigned int val) {
    int low = 0, high = n, mid;

    while (low <= high) {
        mid = (low + high)/2;
        int f = C[mid];
        if (C[mid] < val) low = mid + 1;
        else if (C[mid] > val) high = mid - 1;
        else return mid;
    }

    return -1;
}

bool changeMakingUnlimitedDP(unsigned int C[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    unsigned int error = T+1;
    unsigned int minCoins[n+1][T+1];
    unsigned int lastCoin[n+1][T+1];

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
                int a = valid(i, 0, k, C[i-1]) ? minCoins[i][k-C[i-1]] + 1 : error;
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
    unsigned int i = -1, minCoin = -1;

    for (int j = 0; j <= T; ++j)
        if (minCoins[n][j] < minCoin) {
            i = j;
            minCoin = minCoins[n][j];
        }

    for (i = T; i > 0;) {
        size_t idx = getCoinIdx(C, n, lastCoin[n][i]);
        if (idx == -1) {
            return false;
        }
        usedCoins[idx]++;
        i -= lastCoin[n][i];
        if (i == 0) break;
    }


	return i == 0;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex2, hasChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 1);
    EXPECT_EQ(usedCoins[3], 3);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP4_Ex2, hasChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);
}

TEST(TP4_Ex2, hasNoChange) {
    unsigned int C[] = {5,10};
    unsigned int n = 2;
    unsigned int usedCoins[2];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,1,usedCoins), false);
}