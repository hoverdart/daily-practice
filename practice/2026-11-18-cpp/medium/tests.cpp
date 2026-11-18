#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <random>
#include <vector>
#include "solution.cpp"

// Independent exhaustive partition oracle for small n.
static long long brute(const std::vector<int>& a, int maxGroups) {
    const int n = static_cast<int>(a.size());
    long long best = static_cast<long long>(a.back()) - a.front();
    const int masks = 1 << (n - 1);
    for (int mask = 0; mask < masks; ++mask) {
        int groups = 1;
        int start = 0;
        long long widest = 0;
        for (int i = 0; i + 1 < n; ++i) {
            if (mask & (1 << i)) {
                ++groups;
                widest = std::max(widest,
                    static_cast<long long>(a[i]) - a[start]);
                start = i + 1;
            }
        }
        widest = std::max(widest,
            static_cast<long long>(a.back()) - a[start]);
        if (groups <= maxGroups) best = std::min(best, widest);
    }
    return best;
}

int main() {
    assert(minimumCalibrationSpan({1, 2, 3, 10, 11, 12}, 2) == 2);
    assert(minimumCalibrationSpan({1, 2, 3, 10, 11, 12}, 1) == 11);
    assert(minimumCalibrationSpan({1, 2, 3, 10, 11, 12}, 4) == 1);
    assert(minimumCalibrationSpan({5, 5, 5, 9}, 2) == 0);
    assert(minimumCalibrationSpan({0}, 1) == 0);
    assert(minimumCalibrationSpan({INT_MIN, INT_MAX}, 1) == 4294967295LL);
    assert(minimumCalibrationSpan({INT_MIN, INT_MAX}, 2) == 0);
    assert(minimumCalibrationSpan({-2, -2, -2}, 1) == 0);

    std::mt19937 rng(18112027);
    for (int trial = 0; trial < 3200; ++trial) {
        const int n = 1 + static_cast<int>(rng() % 10);
        const int k = 1 + static_cast<int>(rng() % n);
        std::vector<int> a(n);
        for (int& x : a) x = static_cast<int>(rng() % 35) - 17;
        if (trial % 43 == 0) a[0] = INT_MIN;
        if (trial % 47 == 0) a[n - 1] = INT_MAX;
        std::sort(a.begin(), a.end());
        assert(minimumCalibrationSpan(a, k) == brute(a, k));
    }

    std::vector<int> large(200000);
    for (int i = 0; i < 200000; ++i) large[i] = i;
    assert(minimumCalibrationSpan(large, 1) == 199999);
    assert(minimumCalibrationSpan(large, 2) == 99999);
    assert(minimumCalibrationSpan(large, 200000) == 0);

    std::cout << "medium: all tests passed\n";
}
