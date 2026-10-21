#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

struct Edge {
    int from, to;
    long long cost;
};

long long secondDistinctTransitCost(
    int n, const std::vector<Edge>& edges, int source, int target) {
    using Arc = std::pair<int,long long>;
    std::vector<std::vector<Arc>> adj(n);
    for (const Edge& e : edges)
        adj[e.from].push_back({e.to,e.cost});

    const long long INF = std::numeric_limits<long long>::max()/4;
    std::vector<long long> first(n,INF), second(n,INF);
    using State = std::pair<long long,int>; // (total cost, station)
    std::priority_queue<State,std::vector<State>,std::greater<State>> pq;
    first[source] = 0;
    pq.push({0,source});

    while (!pq.empty()) {
        auto [d,u] = pq.top();
        pq.pop();
        if (d != first[u] && d != second[u]) continue; // stale
        for (auto [v,w] : adj[u]) {
            if (d > INF-w) continue;
            long long candidate = d+w;
            if (candidate < first[v]) {
                second[v] = first[v];
                first[v] = candidate;
                pq.push({candidate,v});
                // Previous first was already queued/processed; it becomes second.
            } else if (candidate > first[v] && candidate < second[v]) {
                second[v] = candidate;
                pq.push({candidate,v});
            }
        }
    }
    return second[target] == INF ? -1 : second[target];
}
