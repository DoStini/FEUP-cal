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

    std::vector<Activity> vec;

    std::sort(A.begin(), A.end(), [](const Activity & a1,const Activity & a2){
        return a1.finish < a2.finish;
    });

    unsigned int lastFinish = -1;

    for (auto & act : A) {
        if(act.start <= lastFinish && act.finish >= lastFinish){
            continue;
        }
        else{
            vec.push_back(act);
            lastFinish = act.finish;
        }
    }

    return vec;
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