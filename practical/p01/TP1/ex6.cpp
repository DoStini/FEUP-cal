// By: Gonçalo Leão

#include "exercises.h"
#include <algorithm>

bool Activity::operator==(const Activity &a2) const {
    return start == a2.start && finish == a2.finish;
}

bool Activity::operator<(const Activity &a2) const {
    return finish < a2.finish;
}

std::vector<Activity> earliestFinishScheduling(std::vector<Activity> A) {

    std::sort(A.begin(), A.end(), [](const Activity & a1,const Activity & a2){
        return a1.finish < a2.finish;
    });

    for (int i = 0; i < A.size(); ++i) {
        for(auto it = A.begin()+i+1; it != A.end();){
            if(it->start <= A[i].finish && it->finish >= A[i].finish){
                it = A.erase(it);
            }
            else
                break;
        }
    }


    return A;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP1_Ex6, activityScheduling) {
    std::vector<Activity> A = {{10,20}, {30, 35}, {5, 15}, {10, 40}, {40, 50}};
    std::vector<Activity> V = earliestFinishScheduling(A);
    EXPECT_EQ(V.size(), 3 );
    ASSERT_THAT(earliestFinishScheduling(A),  ::testing::ElementsAre(Activity(5, 15), Activity(30, 35), Activity(40, 50)));
}