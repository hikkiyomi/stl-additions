#include "../include/stl-algorithms.h"
#include "../include/xrange.h"
#include "../include/zip.h"

#include <iostream>
#include <vector>

int main(int, char**) {
    std::vector<int> a{1, 2, 3};
    std::vector<char> b{'a', 'b', 'c'};
    auto temp = lab::zip(a, b);
    std::vector<std::pair<int, char>> v{temp.begin(), temp.end()};

    for (auto [x, y] : v) {
        std::cout << x << " " << y << "\n";
    }

    return 0;
}
