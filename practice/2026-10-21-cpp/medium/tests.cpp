#include <cassert>
#include <iostream>
#include <limits>
#include <random>
#include <utility>
#include <vector>
#include "solution.cpp"

static std::pair<int,int> brute(const std::vector<int>& a, long long k) {
    int n = static_cast<int>(a.size());
    std::pair<int,int> best = {0,0};
    for (int l = 0; l < n; ++l) {
        for (int r = l+1; r <= n; ++r) {
            long long pairs = 0;
            for (int i = l; i < r; ++i)
                for (int j = i+1; j < r; ++j)
                    if (a[i] == a[j]) ++pairs;
            if (pairs <= k && r-l > best.second-best.first)
                best = {l,r};
        }
    }
    return best;
}
int main() {
    assert((longestLowCollisionWindow({}, 10) == std::pair<int,int>{0,0}));
    assert((longestLowCollisionWindow({1,2,1,2,1},1) == std::pair<int,int>{0,3}));
    assert((longestLowCollisionWindow({5,5,5},0) == std::pair<int,int>{0,1}));
    assert((longestLowCollisionWindow({5,5,5},1) == std::pair<int,int>{0,2}));
    assert((longestLowCollisionWindow({5,5,5},3) == std::pair<int,int>{0,3}));
    assert((longestLowCollisionWindow({9,8,7},0) == std::pair<int,int>{0,3}));
    assert((longestLowCollisionWindow({-1,-1,2,-1,2},2) == brute({-1,-1,2,-1,2},2)));
    std::mt19937 rng(211026);
    for (int tc = 0; tc < 1700; ++tc) {
        int n = static_cast<int>(rng()%16);
        std::vector<int> a(n);
        for (int& x : a) x = static_cast<int>(rng()%9)-4;
        long long k = rng()%30;
        assert(longestLowCollisionWindow(a,k) == brute(a,k));
    }
    std::vector<int> same(200000,7);
    assert((longestLowCollisionWindow(same,499500) == std::pair<int,int>{0,1000}));
    assert((longestLowCollisionWindow(same,20000000000LL) == std::pair<int,int>{0,200000}));
    std::vector<int> distinct(200000);
    for (int i=0;i<200000;++i) distinct[i]=i;
    assert((longestLowCollisionWindow(distinct,0) == std::pair<int,int>{0,200000}));
    std::cout << "medium: all tests passed\n";
}
