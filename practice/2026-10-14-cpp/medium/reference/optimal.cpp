#include <vector>
#include <utility>
#include <deque>
#include <limits>
int minRoadReversals(int n,
                     const std::vector<std::pair<int,int>>& roads,
                     int source, int target) {
    std::vector<std::vector<std::pair<int,int>>> adj(n);
    for (auto [u,v] : roads) {
        adj[u].push_back({v,0});
        adj[v].push_back({u,1});
    }
    const int INF = std::numeric_limits<int>::max() / 4;
    std::vector<int> dist(n, INF);
    std::deque<std::pair<int,int>> dq;
    dist[source] = 0;
    dq.push_front({0,source});
    while (!dq.empty()) {
        auto [d,u] = dq.front(); dq.pop_front();
        if (d != dist[u]) continue;
        for (auto [v,w] : adj[u]) {
            if (d + w >= dist[v]) continue;
            dist[v] = d + w;
            if (w == 0) dq.push_front({dist[v],v});
            else dq.push_back({dist[v],v});
        }
    }
    return dist[target] == INF ? -1 : dist[target];
}
