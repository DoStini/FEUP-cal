#include "exercises.h"

int maxSubsequenceDP(int A[], unsigned int n, unsigned int &i, unsigned int &j) {

    int idxs[n];
    idxs[0] = 0;

    for (int k = 1; k < n; ++k) {
        if (A[k - 1] >= 0) {
            A[k] += A[k - 1];
            idxs[k] = idxs[k - 1];
        } else {
            idxs[k] = k;
        }
    }

    int max = INT32_MIN;

    for (int k = n - 1; k >= 0; --k) {
        if (A[k] > max) {
            max = A[k];
            j = k;
            i = idxs[k];
        }
    }

    return max;
}


#include "../TP1/exercises.h"

int maxSubsequenceBF(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    maxSubsequence(A, n, i, j);
    return 0;
}


#include "../TP3/exercises.h"

int maxSubsequenceDC(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    i = 0, j = n - 1;
    return maxSubs(A, i, j);
    // Copy-paste your solution for ex2 of TP3 HERE
}

void testPerformanceMaxSubsequence() {
    // TODO
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex6, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequenceDP(A1, n1, i, j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDP(A2, n2, i, j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDP(A3, n3, i, j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDP(A4, n4, i, j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);

    testPerformanceMaxSubsequence();
}