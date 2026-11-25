#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>
#include "solution.cpp"

// Independent small-instance time-expanded reachability oracle.
// Positive travel time means every transition moves to a later time.
static long long oracle(const std::vector<long long>& d,
    const std::vector<std::array<int,3>>& edges, int s,int t) {
    const int n=static_cast<int>(d.size());
    const int horizon=static_cast<int>(*std::max_element(d.begin(),d.end()));
    for (int start=static_cast<int>(d[s]);start>=0;--start) {
        std::vector<std::vector<bool>> reach(horizon+1,std::vector<bool>(n));
        reach[start][s]=true;
        for (int time=start;time<=horizon;++time) {
            if (reach[time][t]) return start;
            for (int u=0;u<n;++u)
                if (reach[time][u] && time+1<=d[u]) reach[time+1][u]=true;
            for (const auto& e:edges) {
                int arrival=time+e[2];
                if (reach[time][e[0]] && arrival<=d[e[1]])
                    reach[arrival][e[1]]=true;
            }
        }
    }
    return -1;
}

int main() {
    assert(latestDispatch({20,7,15,18},{{0,1,2},{1,3,3},{0,2,5},{2,3,4}},0,3)==9);
    assert(latestDispatch({20,3,30},{{0,1,4},{1,2,1}},0,2)==-1);
    assert(latestDispatch({8},{},0,0)==8);
    assert(latestDispatch({1,1},{},0,1)==-1);
    assert(latestDispatch({3,3},{{0,1,3}},0,1)==0);
    assert(latestDispatch({10,10},{{0,1,9},{0,1,2},{1,0,1},{0,0,1}},0,1)==8);
    assert(latestDispatch({2,100},{{0,1,1}},0,1)==2);
    assert(latestDispatch({100,4,100},{{0,2,20},{0,1,1},{1,2,1}},0,2)==80);
    assert(latestDispatch({1000000000000LL,1000000000000LL},{{0,1,1000000000}},0,1)==999000000000LL);
    std::mt19937 rng(25112028);
    for (int trial=0;trial<2000;++trial) {
        int n=1+static_cast<int>(rng()%8);
        std::vector<long long> d(n);
        for (auto& x:d) x=rng()%17;
        std::vector<std::array<int,3>> e;
        int m=static_cast<int>(rng()%33);
        for (int i=0;i<m;++i)
            e.push_back({static_cast<int>(rng()%n),static_cast<int>(rng()%n),1+static_cast<int>(rng()%6)});
        int s=static_cast<int>(rng()%n),t=static_cast<int>(rng()%n);
        assert(latestDispatch(d,e,s,t)==oracle(d,e,s,t));
    }
    const int n=100000;
    std::vector<long long> d(n,1000000000000LL);
    std::vector<std::array<int,3>> e;
    for (int i=0;i<n-1;++i) e.push_back({i,i+1,1000000});
    assert(latestDispatch(d,e,0,n-1)==900001000000LL);
    std::cout << "hard: 2000 randomized cases and fixed/stress cases passed\n";
}
