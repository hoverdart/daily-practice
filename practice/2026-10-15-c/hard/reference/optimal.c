#include <limits.h>
#include <stdlib.h>

typedef struct { int from, to, weight; } Edge;

int cheapest_rebate_route(int n, const Edge *edges, int m,
                          int src, int dst, long long *out) {
    const long long INF = LLONG_MAX / 4;
    long long *dist = malloc((size_t)n * sizeof(*dist));
    unsigned char *can_reach_dst = calloc((size_t)n, sizeof(*can_reach_dst));
    if (!dist || !can_reach_dst) { free(dist); free(can_reach_dst); return -1; }
    for (int i = 0; i < n; ++i) dist[i] = INF;
    dist[src] = 0;
    for (int pass = 0; pass < n - 1; ++pass) {
        int changed = 0;
        for (int i = 0; i < m; ++i) {
            Edge e = edges[i];
            if (dist[e.from] != INF && dist[e.from] + e.weight < dist[e.to]) {
                dist[e.to] = dist[e.from] + e.weight;
                changed = 1;
            }
        }
        if (!changed) break;
    }
    /* Reverse reachability via repeated edge scans, O(VE), no adjacency
       allocation needed. Mark every vertex with a path to dst. */
    can_reach_dst[dst] = 1;
    for (int pass = 0; pass < n - 1; ++pass) {
        int changed = 0;
        for (int i = 0; i < m; ++i) {
            Edge e = edges[i];
            if (can_reach_dst[e.to] && !can_reach_dst[e.from]) {
                can_reach_dst[e.from] = 1;
                changed = 1;
            }
        }
        if (!changed) break;
    }
    for (int i = 0; i < m; ++i) {
        Edge e = edges[i];
        if (dist[e.from] != INF && can_reach_dst[e.to] &&
            dist[e.from] + e.weight < dist[e.to]) {
            free(dist); free(can_reach_dst);
            return 1;
        }
    }
    int result = dist[dst] == INF ? -1 : 0;
    if (result == 0) *out = dist[dst];
    free(dist); free(can_reach_dst);
    return result;
}
