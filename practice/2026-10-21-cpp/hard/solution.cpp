#include <vector>

struct Edge {
    int from, to;
    long long cost;
};

long long secondDistinctTransitCost(
    int n, const std::vector<Edge>& edges, int source, int target) {
    // TODO: directed adjacency list + min-heap Dijkstra with
    // two strictly distinct distances for every vertex.
    (void)n; (void)edges; (void)source; (void)target;
    return -1;
}
