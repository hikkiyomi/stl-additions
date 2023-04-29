#include "../include/zip.h"

#include <gtest/gtest.h>

#include <list>
#include <set>

TEST(ZipTest, SameTypesSameContainers) {
    std::vector<int> a = {1, 2, 3, 4};
    std::vector<int> b = {11, 12, 13, 14};
    std::vector<int> c = {5, 6, 7};

    std::vector<std::pair<int, int>> ans1 = {
        {1, 11},
        {2, 12},
        {3, 13},
        {4, 14}
    };

    std::vector<std::pair<int, int>> ans2 = {
        {1, 5},
        {2, 6},
        {3, 7}
    };

    std::vector<std::pair<int, int>> res;

    for (auto [x, y] : lab::zip(a, b)) {
        res.emplace_back(x, y);
    }

    ASSERT_TRUE(res == ans1);
    
    res.clear();

    for (auto [x, y] : lab::zip(a, c)) {
        res.emplace_back(x, y);
    }

    ASSERT_TRUE(res == ans2);
}

TEST(ZipTest, DiffTypesSameContainers) {
    std::vector<int> a = {1, 2, 3, 4};
    std::vector<char> b = {'a', 'b', 'c', 'd'};
    std::vector<std::string> c = {"heh", "huh", "hoh"};

    std::vector<std::pair<int, char>> ans1 = {
        {1, 'a'},
        {2, 'b'},
        {3, 'c'},
        {4, 'd'}
    };

    std::vector<std::pair<int, std::string>> ans2 = {
        {1, "heh"},
        {2, "huh"},
        {3, "hoh"}
    };

    std::vector<std::pair<int, char>> res1;

    for (auto [x, y] : lab::zip(a, b)) {
        res1.emplace_back(x, y);
    }

    ASSERT_TRUE(res1 == ans1);
    
    std::vector<std::pair<int, std::string>> res2;

    for (auto [x, y] : lab::zip(a, c)) {
        res2.emplace_back(x, y);
    }

    ASSERT_TRUE(res2 == ans2);
}

TEST(ZipTest, SameTypesDiffContainers) {
    std::vector<int> a = {1, 2, 3, 4};
    std::list<int> b = {11, 12, 13, 14};
    std::set<int> c = {5, 6, 7};

    std::vector<std::pair<int, int>> ans1 = {
        {1, 11},
        {2, 12},
        {3, 13},
        {4, 14}
    };

    std::vector<std::pair<int, int>> ans2 = {
        {1, 5},
        {2, 6},
        {3, 7}
    };

    std::vector<std::pair<int, int>> res;

    for (auto [x, y] : lab::zip(a, b)) {
        res.emplace_back(x, y);
    }

    ASSERT_TRUE(res == ans1);
    
    res.clear();

    for (auto [x, y] : lab::zip(a, c)) {
        res.emplace_back(x, y);
    }

    ASSERT_TRUE(res == ans2);
}

TEST(ZipTest, DiffTypesDiffContainers) {
    std::vector<int> a = {1, 2, 3, 4};
    std::list<char> b = {'a', 'b', 'c', 'd'};
    std::set<std::string> c = {"heh", "hoh", "huh"};

    std::vector<std::pair<int, char>> ans1 = {
        {1, 'a'},
        {2, 'b'},
        {3, 'c'},
        {4, 'd'}
    };

    std::vector<std::pair<int, std::string>> ans2 = {
        {1, "heh"},
        {2, "hoh"},
        {3, "huh"}
    };

    std::vector<std::pair<int, char>> res1;

    for (auto [x, y] : lab::zip(a, b)) {
        res1.emplace_back(x, y);
    }

    ASSERT_TRUE(res1 == ans1);
    
    std::vector<std::pair<int, std::string>> res2;

    for (auto [x, y] : lab::zip(a, c)) {
        res2.emplace_back(x, y);
    }

    ASSERT_TRUE(res2 == ans2);
}
