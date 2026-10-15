#include <stddef.h>

typedef struct { int from, to, weight; } Edge;

/* Return -1 if dst unreachable, 0 if finite minimum cost (write *out),
   or 1 if a reachable negative cycle can lead to dst (unbounded below).
   Directed edges, negative weights allowed. */
int cheapest_rebate_route(int n, const Edge *edges, int m,
                          int src, int dst, long long *out) {
    (void)n; (void)edges; (void)m; (void)src; (void)dst; (void)out;
    /* TODO: Bellman-Ford, then check whether any improving cycle
       is both reachable from src and can eventually reach dst. */
    return -1;
}
