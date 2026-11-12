#include <stddef.h>

typedef struct { int u, v; } Cable;
typedef struct {
    unsigned char *flags; /* m bytes; caller frees */
    int count;
} BridgeReport;

/* Report bridges by input cable ID, in O(n+m) with iterative DFS.
   Return {NULL,0} when m=0. */
BridgeReport find_bridges(int n, const Cable *edges, int m) {
    (void)n;
    (void)edges;
    (void)m;
    /* TODO:
       - build adjacency arcs tagged with original edge IDs
       - maintain tin/low and a DFS stack with next-neighbor cursors
       - skip exactly the reverse of the DFS parent EDGE ID
       - mark parent-edge bridge when low[child] > tin[parent] */
    BridgeReport answer = {NULL, 0};
    return answer;
}

