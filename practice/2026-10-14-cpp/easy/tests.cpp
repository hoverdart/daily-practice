#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>
#include "solution.cpp"
static int brute(const std::vector<int>& a, int k) {
    int best = 0;
    for (int l = 0; l < static_cast<int>(a.size()); ++l) {
        int zeros = 0;
        for (int r = l; r < static_cast<int>(a.size()); ++r) {
            zeros += a[r] == 0;
            if (zeros <= k) best = std::max(best, r - l + 1);
        }
    }
    return best;
}
int main() {
    assert(longestRepairableRun({}, 3) == 0);
    assert(longestRepairableRun({1,1,1}, 0) == 3);
    assert(longestRepairableRun({0,0,0}, 0) == 0);
    assert(longestRepairableRun({1,0,1,0,1}, 1) == 3);
    assert(longestRepairableRun({1,0,0,1,1,0,1}, 2) == 5);
    assert(longestRepairableRun({0,1,0,1,0}, 2) == 4);
    assert(longestRepairableRun({0,0,0}, 10) == 3);
    assert(longestRepairableRun({1,0,1}, 0) == 1);
    std::mt19937 rng(140026);
    for (int t = 0; t < 1000; ++t) {
        int n = static_cast<int>(rng() % 27);
        std::vector<int> a(n);
        for (int& x : a) x = static_cast<int>(rng() % 2);
        int k = static_cast<int>(rng() % (n + 4));
        assert(longestRepairableRun(a, k) == brute(a, k));
    }
    std::vector<int> large(200000, 1);
    for (int i = 0; i < 200000; i += 3) large[i] = 0;
    assert(longestRepairableRun(large, 200000) == 200000);
    assert(longestRepairableRun(large, 0) == 2);
    std::cout << "easy: all tests passed\n";
}
