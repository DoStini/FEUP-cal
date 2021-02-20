// By: Gonçalo Leão

#include "exercises.h"

unsigned int sumArray(unsigned int a[], unsigned int n) {
    unsigned int sum = 0;
    for(unsigned int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

#include <iostream>

bool isCanonical(unsigned int C[], unsigned int n) {

    unsigned int stock[n];


    unsigned int usedCoinsBF[n];
    unsigned int usedCoinsGR[n];

    unsigned int    infLim = C[2]+1,
                    supLim = C[n-1]+C[n-2];

    for (unsigned int i = infLim + 1; i < supLim; ++i) {
        for (int j = 0; j < n; ++j) {
            stock[j] = i/C[j] + 10;
        }
        changeMakingBF(C, stock, n, i, usedCoinsBF);
        changeMakingGreedy(C, stock, n, i, usedCoinsGR);
        if(sumArray(usedCoinsBF, n) < sumArray(usedCoinsGR, n))
            return false;
    }

    return true;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex5, canonicalTrue) {
    unsigned int C[] = {1,2,5};
    EXPECT_EQ(isCanonical(C,3), true);

    unsigned int C2[] = {1,2,5,10};
    EXPECT_EQ(isCanonical(C2,4), true);
}

TEST(TP1_Ex5, canonicalFalse) {
    unsigned int C[] = {1,4,5};
    EXPECT_EQ(isCanonical(C,3), false);
}