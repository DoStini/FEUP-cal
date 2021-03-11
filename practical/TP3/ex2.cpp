#include "exercises.h"

int maxMid(int A[], int&i, int&j, int x, int y) {
    int sl = 0, sr = 0;

    int currSum = 0;
    int mid = (x+y)/2;
    for (int k = mid; k >= x ; --k) {
        currSum += A[k];
        if (currSum > sl) {
            sl = currSum;
            i = k;
        }
    }

    currSum = 0;
    for (int k = mid+1; k <= y; ++k) {
        currSum += A[k];
        if (currSum > sr) {
            sr = currSum;
            j = k;
        }
    }
    
    return sl + sr;
}

int maxSubs(int A[], int& i, int& j) {
    if (j - i == 0)
        return A[i];

    int split = (i+j)/2;

    int i1 = i, j1 = split,
        i2 = split+1, j2 = j;

    int sl = maxSubs(A, i1, j1);
    int sr = maxSubs(A, i2, j2);
    int im = -1, jm = -1;
    int sm = maxMid(A, im, jm, i,j);

    int sum;
    if(im >= 0 && jm >= 0 && sm > sr && sm > sl) {
        i = im; j = jm;
        return sm;
    }
    bool left = sl > sr;
    i = left ? i1 : i2;
    j = left ? j1 : j2;

    return left ? sl : sr;
}

int maxSubsequenceDC(int A[], unsigned int n, int &i, int &j) {
    i = 0, j = n-1;
    return maxSubs(A, i, j);
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex2, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    int i, j;
    EXPECT_EQ(maxSubsequenceDC(A1,n1,i,j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDC(A2,n2,i,j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDC(A3,n3,i,j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDC(A4,n4,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}