#include <utility>
#include <vector>

struct Road {
    int from, to;
    long long travel;
};

std::pair<long long,int> earliestJointArrival(
    int n, const std::vector<Road>& roads,
    int sourceA, int sourceB, int destination,
    const std::vector<int>& hubs) {
    // TODO:
    // 1. Distances sourceA -> each v.
    // 2. Distances sourceB -> each v.
    // 3. Distances each v -> destination via reverse-graph Dijkstra.
    // 4. Minimize max(distA[v],distB[v]) + distToTarget[v] over hubs.
    (void)n;
    (void)roads;
    (void)sourceA;
    (void)sourceB;
    (void)destination;
    (void)hubs;
    return {-1,-1};
}
