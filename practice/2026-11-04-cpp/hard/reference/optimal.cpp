#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

struct Road {
    int from, to;
    long long travel;
};

using WeightedGraph = std::vector<std::vector<std::pair<int,long long>>>;
static constexpr long long INF_RELAY = std::numeric_limits<long long>::max() / 4;

static std::vector<long long> shortestFrom(const WeightedGraph& graph, int source) {
    using State = std::pair<long long,int>; // (arrival time, vertex)
    std::vector<long long> dist(graph.size(), INF_RELAY);
    std::priority_queue<State, std::vector<State>, std::greater<State>> minHeap;
    dist[source] = 0;
    minHeap.push({0,source});

    while (!minHeap.empty()) {
        auto [time,u] = minHeap.top();
        minHeap.pop();
        if (time != dist[u]) continue; // stale entry
        for (const auto& [v,weight] : graph[u]) {
            if (time + weight < dist[v]) {
                dist[v] = time + weight;
                minHeap.push({dist[v],v});
            }
        }
    }
    return dist;
}

std::pair<long long,int> earliestJointArrival(
    int n, const std::vector<Road>& roads,
    int sourceA, int sourceB, int destination,
    const std::vector<int>& hubs) {
    WeightedGraph forward(n), reverse(n);
    for (const Road& road : roads) {
        forward[road.from].push_back({road.to,road.travel});
        reverse[road.to].push_back({road.from,road.travel});
    }

    const auto aTime = shortestFrom(forward,sourceA);
    const auto bTime = shortestFrom(forward,sourceB);
    const auto toDestination = shortestFrom(reverse,destination);

    long long best = INF_RELAY;
    int bestHub = -1;
    for (int v : hubs) {
        if (aTime[v] == INF_RELAY || bTime[v] == INF_RELAY
            || toDestination[v] == INF_RELAY) continue;

        const long long arrival = std::max(aTime[v],bTime[v]) + toDestination[v];
        if (arrival < best || (arrival == best && (bestHub == -1 || v < bestHub))) {
            best = arrival;
            bestHub = v;
        }
    }
    return bestHub == -1 ? std::make_pair(-1LL,-1) : std::make_pair(best,bestHub);
}
