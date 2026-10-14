#include <vector>
#include <utility>
int minRoadReversals(int n,
                     const std::vector<std::pair<int,int>>& roads,
                     int source, int target) {
    // TODO: each (u,v) creates u->v cost 0 and v->u cost 1.
    // Use a deque and distance relaxation (0-1 BFS).
    (void)n; (void)roads; (void)source; (void)target;
    return -1;
}
