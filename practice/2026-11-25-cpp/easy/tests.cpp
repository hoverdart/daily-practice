#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
#include "solution.cpp"

static std::vector<int> oracle(const std::vector<int>& a) {
    std::vector<int> indices(a.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::stable_sort(indices.begin(), indices.end(),
        [&](int i, int j) { return a[i] > a[j]; });
    return indices;
}

int main() {
    assert(stableDispatch({}).empty());
    assert((stableDispatch({2,5,2,100,5}) == std::vector<int>{3,1,4,0,2}));
    assert((stableDispatch({0,0,0}) == std::vector<int>{0,1,2}));
    assert((stableDispatch({0,100,0,100}) == std::vector<int>{1,3,0,2}));
    std::mt19937 rng(25112026);
    for (int t=0; t<1200; ++t) {
        std::vector<int> a(rng()%101);
        for (int& x : a) x = static_cast<int>(rng()%101);
        const auto before = a;
        assert(stableDispatch(a) == oracle(a));
        assert(a == before);
    }
    std::vector<int> large(200000);
    for (int i=0; i<200000; ++i) large[i] = i%101;
    assert(stableDispatch(large) == oracle(large));
    std::cout << "easy: 1200 randomized cases and fixed/stress cases passed\n";
}
