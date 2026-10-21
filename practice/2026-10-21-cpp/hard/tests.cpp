#include <cassert>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
#include "solution.cpp"

// Independent small-instance oracle: reachability by EXACT total cost.
// Strictly positive edge costs let us scan costs in increasing order.
static long long oracle(int n, const std::vector<Edge>& edges, int s, int t) {
    const int LIMIT = 160; // sufficient for n<=7, weights<=8 in random tests
    std::vector<std::vector<unsigned char>> reach(
        LIMIT+1, std::vector<unsigned char>(n,0));
    reach[0][s] = 1;
    for (int cost=0;cost<=LIMIT;++cost) {
        for (const Edge& e : edges) {
            if (e.cost <= cost &&
                reach[cost-static_cast<int>(e.cost)][e.from])
                reach[cost][e.to] = 1;
        }
    }
    int distinct = 0;
    for (int cost=0;cost<=LIMIT;++cost) {
        if (reach[cost][t] && ++distinct == 2) return cost;
    }
    return -1;
}
int main() {
    assert(secondDistinctTransitCost(3,{{0,1,2},{0,1,4},{1,2,3}},0,2)==7);
    assert(secondDistinctTransitCost(3,{{0,1,2},{0,1,2},{1,2,3}},0,2)==-1);
    assert(secondDistinctTransitCost(2,{{0,1,7},{1,0,4}},0,1)==18);
    assert(secondDistinctTransitCost(2,{{0,1,7},{1,0,4}},0,0)==11);
    assert(secondDistinctTransitCost(1,{},0,0)==-1);
    assert(secondDistinctTransitCost(1,{{0,0,3}},0,0)==3);
    assert(secondDistinctTransitCost(3,{{0,1,1},{1,2,1},{0,2,2},{2,2,1}},0,2)==3);
    assert(secondDistinctTransitCost(3,{{0,1,1000000000LL},
         {1,2,1000000000LL},{0,2,2000000001LL}},0,2)==2000000001LL);
    assert(secondDistinctTransitCost(3,{{0,1,1}},0,2)==-1);
    std::mt19937 rng(212026);
    for (int tc=0;tc<1300;++tc) {
        int n=1+static_cast<int>(rng()%7);
        int m=static_cast<int>(rng()%26);
        std::vector<Edge> e;
        for (int j=0;j<m;++j)
            e.push_back({static_cast<int>(rng()%n),
                         static_cast<int>(rng()%n),
                         1+static_cast<long long>(rng()%8)});
        int s=static_cast<int>(rng()%n), t=static_cast<int>(rng()%n);
        assert(secondDistinctTransitCost(n,e,s,t)==oracle(n,e,s,t));
    }
    const int n=100000;
    std::vector<Edge> chain;
    chain.reserve(n);
    for (int i=0;i<n-1;++i) chain.push_back({i,i+1,1});
    assert(secondDistinctTransitCost(n,chain,0,n-1)==-1);
    chain.push_back({0,n-1,200000});
    assert(secondDistinctTransitCost(n,chain,0,n-1)==200000);
    std::cout << "hard: all tests passed\n";
}
