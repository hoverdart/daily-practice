#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
#include "solution.cpp"
static std::pair<long long,int> slowOracle(
    int n, const std::vector<int>& duration,
    const std::vector<std::pair<int,int>>& edges) {
    constexpr int MOD=1000000007;
    std::vector<std::vector<int>> g(n);
    std::vector<int> indeg(n,0),outdeg(n,0);
    for (auto [u,v]:edges) { g[u].push_back(v); ++indeg[v]; ++outdeg[u]; }
    // Independent cycle check via DFS colors.
    std::vector<int> color(n,0);
    std::function<bool(int)> cycle=[&](int u){
        color[u]=1;
        for (int v:g[u]) {
            if (color[v]==1) return true;
            if (color[v]==0 && cycle(v)) return true;
        }
        color[u]=2;
        return false;
    };
    for (int u=0;u<n;++u) if (color[u]==0 && cycle(u)) return {-1,0};
    long long best=0;
    int ways=0;
    std::function<void(int,long long)> enumerate=[&](int u,long long sum){
        sum+=duration[u];
        if (outdeg[u]==0) {
            if (sum>best) { best=sum; ways=1; }
            else if (sum==best) ways=(ways+1)%MOD;
            return;
        }
        for (int v:g[u]) enumerate(v,sum);
    };
    for (int u=0;u<n;++u) if (indeg[u]==0) enumerate(u,0);
    return {best,ways};
}
static int modPow2(int exp) {
    long long ans=1;
    for (int i=0;i<exp;++i) ans=ans*2%1000000007;
    return static_cast<int>(ans);
}
int main() {
    assert((criticalAssemblyChains(4,{1,2,2,1},{{0,1},{0,2},{1,3},{2,3}})==std::pair<long long,int>{4,2}));
    assert((criticalAssemblyChains(4,{2,2,3,3},{{0,2},{1,2},{0,3},{1,3}})==std::pair<long long,int>{5,4}));
    assert((criticalAssemblyChains(3,{3,5,2},{})==std::pair<long long,int>{5,1}));
    assert((criticalAssemblyChains(2,{1,1},{{0,1},{1,0}})==std::pair<long long,int>{-1,0}));
    assert((criticalAssemblyChains(1,{7},{})==std::pair<long long,int>{7,1}));
    assert((criticalAssemblyChains(3,{1000000000,1000000000,1000000000},{{0,1},{1,2}})==std::pair<long long,int>{3000000000LL,1}));
    assert((criticalAssemblyChains(4,{1,1,1,1},{{0,1},{1,2},{2,1}})==std::pair<long long,int>{-1,0}));
    std::mt19937 rng(141027);
    for (int tc=0;tc<700;++tc) {
        int n=1+static_cast<int>(rng()%8);
        std::vector<int> d(n);
        for (int& x:d) x=1+static_cast<int>(rng()%7);
        std::vector<std::pair<int,int>> edges;
        for (int u=0;u<n;++u) for (int v=u+1;v<n;++v)
            if (rng()%3==0) edges.push_back({u,v});
        if (n>=2 && rng()%5==0) edges.push_back({n-1,0});
        assert(criticalAssemblyChains(n,d,edges)==slowOracle(n,d,edges));
    }
    // 2 choices at each of 40 layers; count must be reduced modulo MOD.
    const int layers=40;
    int n=2*layers+2, sink=n-1;
    std::vector<int> d(n,1);
    std::vector<std::pair<int,int>> edges;
    for (int x=1;x<=2;++x) edges.push_back({0,x});
    for (int layer=1;layer<layers;++layer)
        for (int prev=2*layer-1;prev<=2*layer;++prev)
            for (int next=2*layer+1;next<=2*layer+2;++next)
                edges.push_back({prev,next});
    for (int x=2*layers-1;x<=2*layers;++x) edges.push_back({x,sink});
    assert((criticalAssemblyChains(n,d,edges)==std::pair<long long,int>{layers+2,modPow2(layers)}));
    // Deep DAG: recursive DFS would risk stack overflow, and int would overflow.
    const int big=150000;
    std::vector<int> bigD(big,1000000000);
    std::vector<std::pair<int,int>> chain;
    chain.reserve(big-1);
    for (int i=0;i<big-1;++i) chain.push_back({i,i+1});
    assert((criticalAssemblyChains(big,bigD,chain)==std::pair<long long,int>{150000000000000LL,1}));
    std::cout << "hard: all tests passed\n";
}
