#include <stddef.h>

typedef struct {
    int from, to;
} DirectedEdge;

typedef struct {
    int *indices;   /* caller frees this if non-NULL */
    int count;
} MandatoryEdges;

MandatoryEdges mandatory_fastest_links(
    int n, const DirectedEdge *edges, int m, int source, int target) {
    (void)n;
    (void)edges;
    (void)m;
    (void)source;
    (void)target;
    /* TODO: BFS forward and reverse, then count shortest-route edges by depth. */
    return (MandatoryEdges){NULL, 0};
}

