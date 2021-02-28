#include "exercises.h"

bool Activity::operator==(const Activity &a2) const {
    return start == a2.start && finish == a2.finish;
}

bool Activity::overlaps(const Activity &a2) const {
    return (start < a2.finish) && (a2.start < finish);
}

bool overlaps (const Activity & act, const std::vector<Activity> & vec) {
    for (const auto & a : vec)
        if(act.overlaps(a))
            return true;
    return false;
}

std::vector<Activity> activitySelBack(std::vector<Activity> left, std::vector<Activity> current) {
    if (left.empty())
        return current;

    std::vector<Activity> output = current;

    for (int i = 0; i < left.size(); ++i) {
        if (!overlaps(left[i], current)) {
            Activity curr = left[i];
            left.erase(left.begin() + i);
            current.push_back(curr);

            std::vector<Activity> rec = activitySelBack(left,current);

            if (rec.size() > output.size())
                output = rec;

            left.insert(left.begin(), curr);
            current.pop_back();
        }
    }

    return output;

}

std::vector<Activity> activitySelectionBacktracking(std::vector<Activity> A) {

    return activitySelBack(A, {});
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

bool noOverlaps(const std::vector<Activity> &acts) {
    for(unsigned int i = 0; i < acts.size(); i++) {
        Activity A1 = acts.at(i);
        for(unsigned int j = i + 1; j < acts.size(); j++) {
            Activity A2 = acts.at(j);
            if(A1.overlaps(A2)) return false;
        }
    }
    return true;
}

TEST(TP2_Ex4, activityScheduling) {
    std::vector<Activity> A = {{10,20}, {30, 35}, {5, 15}, {10, 40}, {40, 50}};
    std::vector<Activity> V = activitySelectionBacktracking(A);
    EXPECT_EQ(V.size(), 3);
    EXPECT_EQ(noOverlaps(V), true);
}