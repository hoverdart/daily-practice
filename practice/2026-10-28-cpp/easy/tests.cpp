#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <random>
#include <vector>
#include "solution.cpp"

static int brute(std::vector<int> a, int k) {
    std::sort(a.begin(), a.end(), std::greater<int>());
    return a[k - 1];
}

int main() {
    assert(kthLargestPulse({8,3,8,5},2) == 8);
    assert(kthLargestPulse({8,3,8,5},3) == 5);
    assert(kthLargestPulse({-7,-2,-7},3) == -7);
    assert(kthLargestPulse({42},1) == 42);
    assert(kthLargestPulse({INT_MIN,INT_MAX,0,INT_MAX},2) == INT_MAX);
    std::mt19937 rng(281026);
    for (int t=0; t<1800; ++t) {
        int n=1+static_cast<int>(rng()%90);
        std::vector<int> a(n);
        for (int& x:a) x=static_cast<int>(rng()%41)-20;
        int k=1+static_cast<int>(rng()%n);
        auto before=a;
        assert(kthLargestPulse(a,k)==brute(a,k));
        assert(a==before);
    }
    std::vector<int> large(200000);
    for (int i=0;i<200000;++i) large[i]=i;
    assert(kthLargestPulse(large,1)==199999);
    assert(kthLargestPulse(large,17)==199983);
    assert(kthLargestPulse(large,200000)==0);
    std::vector<int> same(200000,42);
    assert(kthLargestPulse(same,100000)==42);
    std::cout << "easy: all tests passed\n";
}

