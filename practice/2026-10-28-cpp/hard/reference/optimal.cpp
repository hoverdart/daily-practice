#include <algorithm>
#include <numeric>
#include <tuple>
#include <vector>

namespace {
struct DSU {
    std::vector<int> parent, size;
    int components;
    explicit DSU(int n):parent(n),size(n,1),components(n) {
        std::iota(parent.begin(),parent.end(),0);
    }
    int find(int x) {
        while(parent[x]!=x) {
            parent[x]=parent[parent[x]];
            x=parent[x];
        }
        return x;
    }
    bool unite(int a,int b) {
        a=find(a); b=find(b);
        if(a==b) return false;
        if(size[a]<size[b]) std::swap(a,b);
        parent[b]=a;
        size[a]+=size[b];
        --components;
        return true;
    }
};
}

long long minimumCableThreshold(
    int n, const std::vector<std::tuple<int,int,int>>& cables, int k) {
    if(n==1) return 0;

    DSU full(n);
    long long maxWeight=0;
    for(const auto& [u,v,w]:cables) {
        full.unite(u,v);
        maxWeight=std::max(maxWeight,static_cast<long long>(w));
    }
    if(full.components!=1) return -1;

    long long lo=0, hi=maxWeight;
    while(lo<hi) {
        long long mid=lo+(hi-lo)/2;
        DSU cheap(n);
        for(const auto& [u,v,w]:cables)
            if(static_cast<long long>(w)<=mid) cheap.unite(u,v);
        if(cheap.components<=k+1) hi=mid;
        else lo=mid+1;
    }
    return lo;
}

