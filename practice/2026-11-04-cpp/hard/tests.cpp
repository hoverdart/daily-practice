#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <random>
#include <utility>
#include <vector>
#include "solution.cpp"

static std::pair<long long,int> brute(int n,const std::vector<Road>& roads,
                                      int a,int b,int dest,const std::vector<int>& hubs) {
    constexpr long long I=1000000000000000LL;
    std::vector<std::vector<long long>> d(n,std::vector<long long>(n,I));
    for(int i=0;i<n;++i)d[i][i]=0;
    for(const auto& e:roads)d[e.from][e.to]=std::min(d[e.from][e.to],e.travel);
    for(int k=0;k<n;++k)for(int i=0;i<n;++i)for(int j=0;j<n;++j)
        if(d[i][k]!=I&&d[k][j]!=I)
            d[i][j]=std::min(d[i][j],d[i][k]+d[k][j]);
    std::pair<long long,int> best={I,-1};
    for(int v:hubs) {
        if(d[a][v]==I||d[b][v]==I||d[v][dest]==I)continue;
        long long val=std::max(d[a][v],d[b][v])+d[v][dest];
        if(val<best.first||(val==best.first&&(best.second==-1||v<best.second)))
            best={val,v};
    }
    return best.second==-1?std::make_pair(-1LL,-1):best;
}

int main() {
    assert((earliestJointArrival(4,{{0,2,4},{1,2,7},{2,3,3},
                                      {0,3,50},{1,3,20}},0,1,3,{2,3})
            ==std::make_pair(10LL,2)));
    assert((earliestJointArrival(3,{{0,2,1}},0,1,2,{2})
            ==std::make_pair(-1LL,-1)));
    assert((earliestJointArrival(5,{{0,2,1},{1,2,1},{2,4,1},
                                      {0,3,1},{1,3,1},{3,4,1}},0,1,4,{3,2})
            ==std::make_pair(2LL,2)));
    assert((earliestJointArrival(3,{{0,2,5},{0,1,1},{1,2,2}},
                                   0,0,2,{0,1,2})==std::make_pair(3LL,0)));
    assert((earliestJointArrival(1,{},0,0,0,{0,0})
            ==std::make_pair(0LL,0)));
    assert((earliestJointArrival(2,{{0,1,0}},0,1,1,{0,1})
            ==std::make_pair(0LL,1)));
    assert((earliestJointArrival(2,{},0,1,1,{})
            ==std::make_pair(-1LL,-1)));

    std::mt19937 rng(1142026);
    for(int trial=0;trial<1200;++trial) {
        int n=1+static_cast<int>(rng()%9);
        int m=static_cast<int>(rng()%28);
        std::vector<Road> roads;
        for(int e=0;e<m;++e) roads.push_back({
            static_cast<int>(rng()%n),
            static_cast<int>(rng()%n),
            static_cast<int>(rng()%14)
        });
        int a=static_cast<int>(rng()%n),b=static_cast<int>(rng()%n);
        int dest=static_cast<int>(rng()%n);
        std::vector<int> hubs;
        int h=static_cast<int>(rng()%(n+1));
        for(int i=0;i<h;++i)hubs.push_back(static_cast<int>(rng()%n));
        assert(earliestJointArrival(n,roads,a,b,dest,hubs)
               ==brute(n,roads,a,b,dest,hubs));
    }

    constexpr int n=100000;
    std::vector<Road> chain;
    chain.reserve(n-1);
    for(int i=0;i<n-1;++i)chain.push_back({i,i+1,1});
    std::vector<int> hubs;
    for(int i=0;i<n;i+=1000)hubs.push_back(i);
    assert((earliestJointArrival(n,chain,0,50000,n-1,hubs)
            ==std::make_pair(99999LL,50000)));
    std::cout << "hard: all tests passed\n";
}
