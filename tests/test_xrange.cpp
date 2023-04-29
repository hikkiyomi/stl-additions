#include "../include/xrange.h"

#include <gtest/gtest.h>

TEST(XRangeTestSuite, IntTest) {
    auto range1 = lab::xrange(5);
    auto range2 = lab::xrange(3, 5);
    auto range3 = lab::xrange(1, 6, 2);

    std::vector<int> res1;
    std::vector<int> res2;
    std::vector<int> res3;

    for (auto x : range1) {
        res1.push_back(x);
    }

    for (auto x : range2) {
        res2.push_back(x);
    }

    for (auto x : range3) {
        res3.push_back(x);
    }

    ASSERT_TRUE(res1 == std::vector<int>({0, 1, 2, 3, 4}));
    ASSERT_TRUE(res2 == std::vector<int>({3, 4}));
    ASSERT_TRUE(res3 == std::vector<int>({1, 3, 5}));
}

TEST(XRangeTestSuite, FloatTest) {
    auto range1 = lab::xrange(5.0f);
    auto range2 = lab::xrange(3.5f, 5.0f);
    auto range3 = lab::xrange(1.5f, 5.5f, 2.5f);

    std::vector<float> res1;
    std::vector<float> res2;
    std::vector<float> res3;

    for (auto x : range1) {
        res1.push_back(x);
    }

    for (auto x : range2) {
        res2.push_back(x);
    }

    for (auto x : range3) {
        res3.push_back(x);
    }

    ASSERT_TRUE(res1 == std::vector<float>({0.0f, 1.0f, 2.0f, 3.0f, 4.0f}));
    ASSERT_TRUE(res2 == std::vector<float>({3.5f, 4.5f}));
    ASSERT_TRUE(res3 == std::vector<float>({1.5f, 4.0f}));
}

TEST(XRangeTestSuite, InlineTest) {
    std::vector<int> a;

    for (auto x : lab::xrange(1, 6, 2)) {
        a.push_back(x);
    }

    ASSERT_TRUE(a == std::vector<int>({1, 3, 5}));
}

TEST(XRangeTestSuite, BackwardTest) {
    std::vector<int> a;

    for (auto x : lab::xrange(6, 1, -2)) {
        a.push_back(x);
    }

    ASSERT_TRUE(a == std::vector<int>({6, 4, 2}));
}
