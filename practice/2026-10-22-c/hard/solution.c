#include <stddef.h>

typedef struct { int u, v; } Edge;

/* Write bridge edge IDs in ascending input order. Return count, or -1 on OOM. */
int find_critical_links(int n, const Edge *edges, int m, int *out_ids) {
    (void)n; (void)edges; (void)m; (void)out_ids;
    /* TODO: build edge-ID adjacency lists; iterative DFS with tin/low. */
    return 0;
}
