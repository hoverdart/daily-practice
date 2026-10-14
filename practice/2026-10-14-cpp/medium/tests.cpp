#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <random>
#include <utility>
#include <vector>
#include "solution.cpp"
static int slowDijkstra(int n, const std::vector<std::pair<int,int>>& roads, int s, int t) {
    std::vector<std::vector<std::pair<int,int>>> g(n);
    for (auto [u,v] : roads) { g[u].push_back({v,0}); g[v].push_back({u,1}); }
    const int INF = 1000000000;
    std::vector<int> d(n, INF);
    using P = std::pair<int,int>;
    std::priority_queue<P,std::vector<P>,std::greater<P>> pq;
    d[s] = 0; pq.push({0,s});
    while (!pq.empty()) {
        auto [du,u] = pq.top(); pq.pop();
        if (du != d[u]) continue;
        for (auto [v,w] : g[u]) if (du + w < d[v]) {
            d[v] = du + w; pq.push({d[v],v});
        }
    }
    return d[t] == INF ? -1 : d[t];
}
int main() {
    assert(minRoadReversals(4, {{0,1},{2,1},{2,3}}, 0, 3) == 1);
    assert(minRoadReversals(3, {{1,0},{2,1}}, 0, 2) == 2);
    assert(minRoadReversals(3, {{0,1},{1,2}}, 0, 2) == 0);
    assert(minRoadReversals(3, {{0,1},{1,2}}, 2, 0) == 2);
    assert(minRoadReversals(5, {{0,1},{2,3}}, 0, 3) == -1);
    assert(minRoadReversals(1, {}, 0, 0) == 0);
    assert(minRoadReversals(3, {{0,0},{0,1},{0,1},{2,1}}, 0, 2) == 1);
    std::mt19937 rng(141026);
    for (int tc = 0; tc < 700; ++tc) {
        int n = 1 + static_cast<int>(rng() % 12);
        int m = static_cast<int>(rng() % 55);
        std::vector<std::pair<int,int>> roads;
        for (int j=0; j<m; ++j)
            roads.push_back({static_cast<int>(rng()%n),static_cast<int>(rng()%n)});
        int s=static_cast<int>(rng()%n), t=static_cast<int>(rng()%n);
        assert(minRoadReversals(n, roads, s, t) == slowDijkstra(n, roads, s, t));
    }
    const int n=150000;
    std::vector<std::pair<int,int>> chain;
    chain.reserve(n-1);
    for (int i=1;i<n;++i) chain.push_back({i,i-1});
    assert(minRoadReversals(n, chain, 0, n-1) == n-1);
    assert(minRoadReversals(n, chain, n-1, 0) == 0);
    std::cout << "medium: all tests passed\n";
}
