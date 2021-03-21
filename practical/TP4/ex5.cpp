#include "exercises.h"

unsigned long s_recursive(unsigned int n, unsigned int k) {
    if(n == 1 || k == 1 || k == n) {
        return 1;
    }
    return s_recursive(n-1, k-1) + k*s_recursive(n-1, k);
}

unsigned long b_recursive(unsigned int n) {
    unsigned long sum = 0;
    for (unsigned int i = 1; i <= n; ++i) {
        sum += s_recursive(n,i);
    }
    return sum;
}


unsigned long s_dynamic(unsigned int n, unsigned int k) {
    int comb[k];

    for (unsigned int i = 0; i < k; ++i)
        comb[i] = 1;

    for (unsigned int i = 3; i <= n; ++i) {
        for (unsigned int j = std::min(i-1, k); j > 1; --j) {
            comb[j-1] = comb[j-2] + j*comb[j-1];
        }
    }

    return comb[k-1];
}

unsigned long b_dynamic(unsigned int n) {
    int comb[n];

    for (unsigned int i = 0; i < n; ++i)
        comb[i] = 1;

    for (unsigned int i = 3; i <= n; ++i) {
        for (unsigned int j = std::min(i-1, n); j > 1; --j) {
            comb[j-1] = comb[j-2] + j*comb[j-1];
        }
    }
    unsigned sum = 0;
    for (unsigned int i = 0; i < n; ++i)
        sum += comb[i];
    return sum;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex5, testPartitioningRecursive) {
    EXPECT_EQ(1,s_recursive(3,3));
    EXPECT_EQ(3025,s_recursive(9,3));
    EXPECT_EQ(22827,s_recursive(10,6));

    EXPECT_EQ(5,b_recursive(3));
    EXPECT_EQ(203,b_recursive(6));
    EXPECT_EQ(1382958545,b_recursive(15));
}

TEST(TP4_Ex5, testPartitioningDynamic) {
    EXPECT_EQ(1,s_dynamic(3,3));
    EXPECT_EQ(3025,s_dynamic(9,3));
    EXPECT_EQ(22827,s_dynamic(10,6));

    EXPECT_EQ(5,b_dynamic(3));
    EXPECT_EQ(203,b_dynamic(6));
    EXPECT_EQ(1382958545,b_dynamic(15));
}