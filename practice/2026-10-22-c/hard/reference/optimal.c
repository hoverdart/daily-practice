#include <stddef.h>
#include <stdlib.h>

typedef struct { int u, v; } Edge;

int find_critical_links(int n, const Edge *edges, int m, int *out_ids) {
    int *head = NULL, *to = NULL, *next = NULL, *edge_id = NULL;
    int *tin = NULL, *low = NULL, *parent = NULL, *parent_edge = NULL;
    int *cursor = NULL, *stack = NULL;
    unsigned char *bridge = NULL;
    int answer = -1;
    size_t arcs = m ? (size_t)2 * (size_t)m : 1u;
    head = malloc((size_t)n * sizeof *head);
    to = malloc(arcs * sizeof *to);
    next = malloc(arcs * sizeof *next);
    edge_id = malloc(arcs * sizeof *edge_id);
    tin = malloc((size_t)n * sizeof *tin);
    low = malloc((size_t)n * sizeof *low);
    parent = malloc((size_t)n * sizeof *parent);
    parent_edge = malloc((size_t)n * sizeof *parent_edge);
    cursor = malloc((size_t)n * sizeof *cursor);
    stack = malloc((size_t)n * sizeof *stack);
    bridge = calloc(m ? (size_t)m : 1u, sizeof *bridge);
    if (!head || !to || !next || !edge_id || !tin || !low || !parent ||
        !parent_edge || !cursor || !stack || !bridge) goto cleanup;
    for (int v = 0; v < n; ++v) { head[v] = -1; tin[v] = -1; }
    int arc_count = 0;
    for (int id = 0; id < m; ++id) {
        int u = edges[id].u, v = edges[id].v;
        to[arc_count] = v; edge_id[arc_count] = id;
        next[arc_count] = head[u]; head[u] = arc_count++;
        to[arc_count] = u; edge_id[arc_count] = id;
        next[arc_count] = head[v]; head[v] = arc_count++;
    }
    int timer = 0, top = 0;
    for (int root = 0; root < n; ++root) {
        if (tin[root] != -1) continue;
        parent[root] = -1;
        parent_edge[root] = -1;
        tin[root] = low[root] = timer++;
        cursor[root] = head[root];
        stack[top++] = root;
        while (top) {
            int u = stack[top - 1];
            int arc = cursor[u];
            if (arc == -1) {
                --top;
                int p = parent[u];
                if (p != -1) {
                    if (low[u] > tin[p]) bridge[parent_edge[u]] = 1;
                    if (low[u] < low[p]) low[p] = low[u];
                }
                continue;
            }
            cursor[u] = next[arc];
            int v = to[arc], id = edge_id[arc];
            if (id == parent_edge[u]) continue;
            if (tin[v] == -1) {
                parent[v] = u;
                parent_edge[v] = id;
                tin[v] = low[v] = timer++;
                cursor[v] = head[v];
                stack[top++] = v;
            } else if (tin[v] < low[u]) {
                low[u] = tin[v];
            }
        }
    }
    answer = 0;
    for (int id = 0; id < m; ++id) if (bridge[id]) out_ids[answer++] = id;
cleanup:
    free(head); free(to); free(next); free(edge_id);
    free(tin); free(low); free(parent); free(parent_edge);
    free(cursor); free(stack); free(bridge);
    return answer;
}
