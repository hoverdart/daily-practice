#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <map>
#include <random>
#include <utility>
#include <vector>
#include "solution.cpp"

static std::pair<int, int> brute(
    const std::vector<int>& stations, int k) {
    std::pair<int, int> best{0, 0};
    for (int left = 0; left < static_cast<int>(stations.size()); ++left) {
        std::map<std::pair<int, int>, int> freq;
        int repeats = 0;
        for (int right = left; right < static_cast<int>(stations.size()); ++right) {
            if (right > left) {
                const int a = std::min(stations[right - 1], stations[right]);
                const int b = std::max(stations[right - 1], stations[right]);
                if (++freq[{a, b}] > 1) ++repeats;
            }
            if (repeats > k) break;
            const int length = right - left + 1;
            if (length > best.second) best = {left, length};
        }
    }
    return best;
}

int main() {
    assert((longestHandoffTrace({5, 7, 5, 9, 7, 9}, 1)
            == std::make_pair(0, 5)));
    assert((longestHandoffTrace({}, 0) == std::make_pair(0, 0)));
    assert((longestHandoffTrace({42}, 0) == std::make_pair(0, 1)));
    assert((longestHandoffTrace({3, 3, 3, 3}, 0) == std::make_pair(0, 2)));
    assert((longestHandoffTrace({3, 3, 3, 3}, 1) == std::make_pair(0, 3)));
    assert((longestHandoffTrace({3, 3, 3, 3}, 2) == std::make_pair(0, 4)));
    assert((longestHandoffTrace({INT_MIN, -1, INT_MIN}, 0)
            == std::make_pair(0, 2)));
    assert((longestHandoffTrace({1, 2, 3, 1, 2}, 0)
            == std::make_pair(0, 4)));

    std::mt19937 rng(11112027);
    for (int trial = 0; trial < 3200; ++trial) {
        const int n = static_cast<int>(rng() % 25);
        const int k = static_cast<int>(rng() % 9);
        std::vector<int> stations(n);
        for (int& station : stations) {
            station = static_cast<int>(rng() % 7) - 3;
        }
        if (n > 0 && trial % 9 == 0) stations[0] = INT_MIN;
        if (n > 1 && trial % 13 == 0) stations[1] = INT_MAX;
        assert(longestHandoffTrace(stations, k) == brute(stations, k));
    }

    constexpr int n = 200000;
    const std::vector<int> allSame(n, -5);
    assert((longestHandoffTrace(allSame, 0) == std::make_pair(0, 2)));
    assert((longestHandoffTrace(allSame, 7) == std::make_pair(0, 9)));
    std::vector<int> distinct(n);
    for (int i = 0; i < n; ++i) distinct[i] = i - 100000;
    assert((longestHandoffTrace(distinct, 0) == std::make_pair(0, n)));

    std::cout << "medium: all tests passed\n";
}
