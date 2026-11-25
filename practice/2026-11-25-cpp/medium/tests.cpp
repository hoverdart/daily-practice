#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>
#include "solution.cpp"

static int oracle(const std::vector<int>& a, long long budget) {
    int best=0, n=static_cast<int>(a.size());
    for (int l=0; l<n; ++l) {
        long long sum=0;
        int largest=0;
        for (int r=l; r<n; ++r) {
            sum += a[r];
            largest = std::max(largest,a[r]);
            if (sum-largest <= budget) best=std::max(best,r-l+1);
        }
    }
    return best;
}
int main() {
    assert(longestFreeSpan({},7)==0);
    assert(longestFreeSpan({4,9,2,3},5)==3);
    assert(longestFreeSpan({8,1,1,8},2)==3);
    assert(longestFreeSpan({0,0,0},0)==3);
    assert(longestFreeSpan({100},0)==1);
    assert(longestFreeSpan({4,4,4},4)==2);
    assert(longestFreeSpan({10,1,1,1,6,6},3)==4);
    assert(longestFreeSpan({1000000000,1000000000,1000000000},2000000000LL)==3);
    std::mt19937 rng(25112027);
    for (int t=0; t<1800; ++t) {
        std::vector<int> a(rng()%45);
        for (int& x:a) x=static_cast<int>(rng()%30);
        long long budget=rng()%100;
        assert(longestFreeSpan(a,budget)==oracle(a,budget));
    }
    std::vector<int> large(200000,1000000000);
    assert(longestFreeSpan(large,99999999999LL)==100);
    assert(longestFreeSpan(large,200000000000000LL)==200000);
    std::cout << "medium: 1800 randomized cases and fixed/stress cases passed\n";
}
