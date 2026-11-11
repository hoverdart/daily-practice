#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <random>
#include <vector>
#include "solution.cpp"

static std::vector<int> brute(
    const std::vector<int>& ids, const std::vector<IdRange>& queries) {
    std::vector<int> result;
    for (const auto& q : queries) {
        int count = 0;
        for (int x : ids) {
            if (q.low <= x && x <= q.high) ++count;
        }
        result.push_back(count);
    }
    return result;
}

int main() {
    const std::vector<int> ids{-3, -3, 0, 2, 2, 2, 9};
    const std::vector<IdRange> queries{
        {-3, -3}, {1, 8}, {-3, 2}, {4, 3},
        {10, 20}, {INT_MIN, INT_MAX}, {2, 2}
    };
    assert((archiveRangeCounts(ids, queries) ==
            std::vector<int>{2, 3, 6, 0, 0, 7, 3}));
    assert(archiveRangeCounts({}, {{0, 0}, {INT_MIN, INT_MAX}})
           == std::vector<int>({0, 0}));
    assert(archiveRangeCounts({1, 1}, {}).empty());
    assert((archiveRangeCounts({INT_MIN, INT_MAX},
            {{INT_MIN, INT_MIN}, {INT_MAX, INT_MAX}, {INT_MIN, INT_MAX}})
            == std::vector<int>{1, 1, 2}));

    std::mt19937 rng(11112026);
    for (int trial = 0; trial < 2800; ++trial) {
        const int n = static_cast<int>(rng() % 61);
        const int q = static_cast<int>(rng() % 45);
        std::vector<int> values;
        for (int i = 0; i < n; ++i) {
            values.push_back(static_cast<int>(rng() % 41) - 20);
        }
        std::sort(values.begin(), values.end());
        std::vector<IdRange> ranges;
        for (int i = 0; i < q; ++i) {
            ranges.push_back({
                static_cast<int>(rng() % 61) - 30,
                static_cast<int>(rng() % 61) - 30
            });
        }
        assert(archiveRangeCounts(values, ranges) == brute(values, ranges));
    }

    constexpr int n = 200000;
    const std::vector<int> repeated(n, 42);
    std::vector<IdRange> many;
    many.reserve(n);
    for (int i = 0; i < n; ++i) {
        many.push_back(i % 2 == 0 ? IdRange{42, 42} : IdRange{43, INT_MAX});
    }
    const auto result = archiveRangeCounts(repeated, many);
    assert(result.size() == static_cast<size_t>(n));
    for (int i = 0; i < n; ++i) {
        assert(result[i] == (i % 2 == 0 ? n : 0));
    }
    std::cout << "easy: all tests passed\n";
}
