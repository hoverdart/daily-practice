#include <stddef.h>
#include <stdlib.h>

typedef struct { int u, v; } Cable;
typedef struct {
    unsigned char *flags; /* m bytes; caller frees */
    int count;
} BridgeReport;

BridgeReport find_bridges(int n, const Cable *edges, int m) {
    BridgeReport result = {NULL, 0};
    if (m == 0) return result;

    size_t arcs = (size_t)2 * (size_t)m;
    int *head = malloc((size_t)n * sizeof(int));
    int *to = malloc(arcs * sizeof(int));
    int *next = malloc(arcs * sizeof(int));
    int *tin = malloc((size_t)n * sizeof(int));
    int *low = malloc((size_t)n * sizeof(int));
    int *parent = malloc((size_t)n * sizeof(int));
    int *parent_edge = malloc((size_t)n * sizeof(int));
    int *cursor = malloc((size_t)n * sizeof(int));
    int *stack = malloc((size_t)n * sizeof(int));
    result.flags = calloc((size_t)m, sizeof(unsigned char));

    if (!head || !to || !next || !tin || !low || !parent ||
        !parent_edge || !cursor || !stack || !result.flags)
        goto allocation_failure;

    for (int v = 0; v < n; ++v) {
        head[v] = -1;
        tin[v] = -1;
    }
    for (int e = 0; e < m; ++e) {
        int u = edges[e].u, v = edges[e].v;
        int a = 2 * e, b = a + 1;
        to[a] = v; next[a] = head[u]; head[u] = a;
        to[b] = u; next[b] = head[v]; head[v] = b;
    }

    int clock = 0;
    for (int root = 0; root < n; ++root) {
        if (tin[root] != -1) continue;
        int top = 0;
        stack[top++] = root;
        tin[root] = low[root] = clock++;
        parent[root] = parent_edge[root] = -1;
        cursor[root] = head[root];

        while (top > 0) {
            int u = stack[top - 1];

            if (cursor[u] == -1) {
                --top; /* return from DFS(u) */
                int p = parent[u];
                if (p != -1) {
                    if (low[u] > tin[p]) {
                        result.flags[parent_edge[u]] = 1;
                        ++result.count;
                    }
                    if (low[u] < low[p]) low[p] = low[u];
                }
                continue;
            }

            int arc = cursor[u];
            cursor[u] = next[arc]; /* resume here after child finishes */
            int edge_id = arc / 2;
            if (edge_id == parent_edge[u]) continue;
            int v = to[arc];

            if (tin[v] == -1) {
                parent[v] = u;
                parent_edge[v] = edge_id;
                tin[v] = low[v] = clock++;
                cursor[v] = head[v];
                stack[top++] = v;
            } else if (tin[v] < low[u]) {
                low[u] = tin[v]; /* visited ancestor/back edge */
            }
        }
    }

    free(head); free(to); free(next); free(tin); free(low);
    free(parent); free(parent_edge); free(cursor); free(stack);
    return result;

allocation_failure:
    free(head); free(to); free(next); free(tin); free(low);
    free(parent); free(parent_edge); free(cursor); free(stack);
    free(result.flags);
    result.flags = NULL;
    result.count = 0;
    return result;
}

