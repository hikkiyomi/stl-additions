#include "../include/stl-algorithms.h"

#include <gtest/gtest.h>

#include <list>
#include <vector>

TEST(AlgorithmTestSuite, AllOfTest) {
    std::vector<int> a = {1, 2, 3, 4, 5};

    auto f = [](int x) {
        return x < 6;
    };
    
    auto g = [](int x) {
        return x < 5;
    };

    ASSERT_TRUE(std::all_of(a.begin(), a.end(), f) == lab::all_of(a.begin(), a.end(), f));
    ASSERT_TRUE(std::all_of(a.begin(), a.end(), g) == lab::all_of(a.begin(), a.end(), g));
}

TEST(AlgorithmTestSuite, AnyOfTest) {
    std::vector<int> a = {1, 2, 3, 4, 5};

    auto f = [](int x) {
        return x == 6;
    };
    
    auto g = [](int x) {
        return x == 5;
    };

    ASSERT_TRUE(std::any_of(a.begin(), a.end(), f) == lab::any_of(a.begin(), a.end(), f));
    ASSERT_TRUE(std::any_of(a.begin(), a.end(), g) == lab::any_of(a.begin(), a.end(), g));
}

TEST(AlgorithmTestSuite, NoneOfTest) {
    std::vector<int> a = {1, 2, 3, 4, 5};

    auto f = [](int x) {
        return x == 6;
    };
    
    auto g = [](int x) {
        return x == 5;
    };

    ASSERT_TRUE(std::none_of(a.begin(), a.end(), f) == lab::none_of(a.begin(), a.end(), f));
    ASSERT_TRUE(std::none_of(a.begin(), a.end(), g) == lab::none_of(a.begin(), a.end(), g));
}

TEST(AlgorithmTestSuite, OneOfTest) {
    std::vector<int> a = {1, 2, 3, 4, 5, 1};

    auto f = [](int x) {
        return x == 6;
    };
    
    auto g = [](int x) {
        return x == 5;
    };

    auto h = [](int x) {
        return x == 1;
    };

    ASSERT_TRUE((std::count_if(a.begin(), a.end(), f) == 1) == lab::one_of(a.begin(), a.end(), f));
    ASSERT_TRUE((std::count_if(a.begin(), a.end(), g) == 1) == lab::one_of(a.begin(), a.end(), g));
    ASSERT_TRUE((std::count_if(a.begin(), a.end(), h) == 1) == lab::one_of(a.begin(), a.end(), h));
}

TEST(AlgorithmTestSuite, IsSortedTest) {
    std::vector<std::vector<int>> vecs = {
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
        {1, 2, 5, 4, 3}
    };

    auto comp = [](int a, int b) {
        return a > b;
    };

    for (const auto& vec : vecs) {
        ASSERT_TRUE(std::is_sorted(vec.begin(), vec.end()) == lab::is_sorted(vec.begin(), vec.end()));
        ASSERT_TRUE(std::is_sorted(vec.rbegin(), vec.rend()) == lab::is_sorted(vec.rbegin(), vec.rend()));

        ASSERT_TRUE(std::is_sorted(vec.begin(), vec.end(), comp) == lab::is_sorted(vec.begin(), vec.end(), comp));
        ASSERT_TRUE(std::is_sorted(vec.rbegin(), vec.rend(), comp) == lab::is_sorted(vec.rbegin(), vec.rend(), comp));
    }
}

TEST(AlgorithmTestSuite, IsPartitionedTest) {
    std::vector<int> a = {2, 4, 1, 3, 5};

    auto f = [](int x) {
        return x % 2 == 0;
    };

    auto g = [](int x) {
        return x % 3 == 0;
    };

    ASSERT_TRUE(std::is_partitioned(a.begin(), a.end(), f) == std::is_partitioned(a.begin(), a.end(), f));
    ASSERT_TRUE(std::is_partitioned(a.begin(), a.end(), g) == std::is_partitioned(a.begin(), a.end(), g));
}

TEST(AlgorithmTestSuite, FindNotTest) {
    std::vector<int> a = {1, 1, 1, 1, 2, 3, 1};
    std::list<int> b = {2, 2, 2, 2, 1000};

    ASSERT_TRUE(*lab::find_not(a.begin(), a.end(), 1) == 2);
    ASSERT_TRUE(*lab::find_not(b.begin(), b.end(), 2) == 1000);
}

TEST(AlgorithmTestSuite, FindBackwardTest) {
    std::vector<int> a = {1, 2, 1, 1, 1, 3, 4, 5};

    ASSERT_TRUE(lab::find_backward(a.begin(), a.end(), 1) == (a.begin() + 4));
}

TEST(AlgorithmTestSuite, IsPalindromeTest) {
    std::vector<int> a = {1, 2, 3, 4, 5};
    std::vector<int> b = {1, 2, 3, 2, 1};

    auto f = [](int x, int y) {
        return x % 2 == y % 2;
    };

    ASSERT_TRUE(!lab::is_palindrome(a.begin(), a.end()));
    ASSERT_TRUE(lab::is_palindrome(a.begin(), a.end(), f));

    ASSERT_TRUE(lab::is_palindrome(b.begin(), b.end()));
    ASSERT_TRUE(lab::is_palindrome(b.begin(), b.end(), f));
}
