#include <cassert>
#include <iostream>
#include <random>
#include <vector>
#include "solution.cpp"

static long long brute(const std::vector<int>& a, long long k) {
    long long ans=0;
    for (int l=0;l<static_cast<int>(a.size());++l)
        for (int r=l;r<static_cast<int>(a.size());++r) {
            long long pairs=0;
            for (int i=l;i<=r;++i)
                for (int j=i+1;j<=r;++j)
                    if (a[i]==a[j]) ++pairs;
            if (pairs>=k) ++ans;
        }
    return ans;
}
int main() {
    assert(countOverloadedWindows({},0)==0);
    assert(countOverloadedWindows({},1)==0);
    assert(countOverloadedWindows({1,1,1},1)==3);
    assert(countOverloadedWindows({1,1,1},2)==1);
    assert(countOverloadedWindows({2,2,3,2},2)==1);
    assert(countOverloadedWindows({7,8,9},1)==0);
    assert(countOverloadedWindows({7,8,9},0)==6);
    assert(countOverloadedWindows({-1,-1,-1,-1},3)==3);
    std::mt19937 rng(281027);
    for (int t=0;t<1700;++t) {
        int n=static_cast<int>(rng()%13);
        std::vector<int> a(n);
        for (int& x:a) x=static_cast<int>(rng()%7)-3;
        long long k=rng()%35;
        assert(countOverloadedWindows(a,k)==brute(a,k));
    }
    const long long n=200000;
    std::vector<int> same(static_cast<size_t>(n),17);
    assert(countOverloadedWindows(same,0)==n*(n+1)/2);
    assert(countOverloadedWindows(same,1)==n*(n-1)/2);
    assert(countOverloadedWindows(same,n*(n-1)/2)==1);
    assert(countOverloadedWindows(same,n*(n-1)/2+1)==0);
    std::vector<int> distinct(static_cast<size_t>(n));
    for (int i=0;i<n;++i) distinct[i]=i;
    assert(countOverloadedWindows(distinct,1)==0);
    std::cout << "medium: all tests passed\n";
}

