#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <random>
#include <tuple>
#include <vector>
#include "solution.cpp"

struct BruteDSU {
    std::vector<int> p;
    int components;
    explicit BruteDSU(int n):p(n),components(n) {
        for (int i=0;i<n;++i) p[i]=i;
    }
    int find(int a) {while(p[a]!=a) a=p[a];return a;}
    bool join(int a,int b) {
        a=find(a);b=find(b);
        if(a==b) return false;
        p[b]=a;--components;return true;
    }
};

static long long brute(int n,const std::vector<std::tuple<int,int,int>>& e,int k) {
    if(n==1) return 0;
    int m=static_cast<int>(e.size());
    long long best=LLONG_MAX;
    for(int mask=0;mask<(1<<m);++mask) {
        if(__builtin_popcount(static_cast<unsigned>(mask))!=n-1) continue;
        BruteDSU d(n);
        std::vector<int> chosen;
        bool cycle=false;
        for(int j=0;j<m;++j) if(mask&(1<<j)) {
            auto [u,v,w]=e[j];
            if(!d.join(u,v)){cycle=true;break;}
            chosen.push_back(w);
        }
        if(cycle || d.components!=1) continue;
        std::sort(chosen.begin(),chosen.end(),std::greater<int>());
        long long threshold=k>=n-1 ? 0 : chosen[k];
        best=std::min(best,threshold);
    }
    return best==LLONG_MAX ? -1 : best;
}

int main() {
    const std::vector<std::tuple<int,int,int>> sample={
        {0,1,3},{1,2,9},{2,3,5},{0,3,20}};
    assert(minimumCableThreshold(4,sample,0)==9);
    assert(minimumCableThreshold(4,sample,1)==5);
    assert(minimumCableThreshold(4,sample,2)==3);
    assert(minimumCableThreshold(4,sample,3)==0);
    assert(minimumCableThreshold(3,{{0,1,2}},0)==-1);
    assert(minimumCableThreshold(1,{},0)==0);
    assert(minimumCableThreshold(2,{{0,0,1},{0,1,100},{0,1,2}},0)==2);
    assert(minimumCableThreshold(2,{{0,0,1},{0,1,100},{0,1,2}},1)==0);
    assert(minimumCableThreshold(2,{{0,1,1000000000}},0)==1000000000LL);
    std::mt19937 rng(281028);
    for(int t=0;t<2200;++t) {
        int n=1+static_cast<int>(rng()%7);
        int m=static_cast<int>(rng()%11);
        std::vector<std::tuple<int,int,int>> e;
        for(int j=0;j<m;++j)
            e.emplace_back(static_cast<int>(rng()%n),
                           static_cast<int>(rng()%n),
                           1+static_cast<int>(rng()%13));
        int k=static_cast<int>(rng()%n);
        assert(minimumCableThreshold(n,e,k)==brute(n,e,k));
    }
    const int n=200000;
    std::vector<std::tuple<int,int,int>> chain;
    chain.reserve(n-1);
    for(int i=1;i<n;++i) chain.emplace_back(i-1,i,i);
    assert(minimumCableThreshold(n,chain,0)==n-1);
    assert(minimumCableThreshold(n,chain,100)==n-101);
    assert(minimumCableThreshold(n,chain,n-1)==0);
    std::cout << "hard: all tests passed\n";
}

