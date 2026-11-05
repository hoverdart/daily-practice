#include <stddef.h>
#include <stdlib.h>

typedef struct {
    int from, to;
} DirectedEdge;

typedef struct {
    int *indices;
    int count;
} MandatoryEdges;

/* head/next represents edge IDs; reverse selects which endpoint is the neighbor. */
static void bfs_shortest(
    int n, const DirectedEdge *edges, const int *head, const int *next,
    int start, int reverse, int *dist, int *queue) {
    for (int v = 0; v < n; ++v) dist[v] = -1;
    int front = 0, back = 0;
    dist[start] = 0;
    queue[back++] = start;
    while (front < back) {
        int u = queue[front++];
        for (int e = head[u]; e != -1; e = next[e]) {
            int v = reverse ? edges[e].from : edges[e].to;
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                queue[back++] = v;
            }
        }
    }
}

MandatoryEdges mandatory_fastest_links(
    int n, const DirectedEdge *edges, int m, int source, int target) {
    MandatoryEdges result = {NULL, 0};
    if (source == target) return result;

    size_t edge_slots = (size_t)(m > 0 ? m : 1);
    int *forward_head = malloc((size_t)n * sizeof(int));
    int *reverse_head = malloc((size_t)n * sizeof(int));
    int *forward_next = malloc(edge_slots * sizeof(int));
    int *reverse_next = malloc(edge_slots * sizeof(int));
    int *dist_s = malloc((size_t)n * sizeof(int));
    int *dist_t = malloc((size_t)n * sizeof(int));
    int *queue = malloc((size_t)n * sizeof(int));
    if (!forward_head || !reverse_head || !forward_next || !reverse_next ||
        !dist_s || !dist_t || !queue) goto cleanup;

    for (int v = 0; v < n; ++v) {
        forward_head[v] = -1;
        reverse_head[v] = -1;
    }
    for (int e = 0; e < m; ++e) {
        int u = edges[e].from, v = edges[e].to;
        forward_next[e] = forward_head[u];
        forward_head[u] = e;
        reverse_next[e] = reverse_head[v];
        reverse_head[v] = e;
    }

    bfs_shortest(n, edges, forward_head, forward_next, source, 0, dist_s, queue);
    bfs_shortest(n, edges, reverse_head, reverse_next, target, 1, dist_t, queue);

    int D = dist_s[target];
    if (D <= 0) goto cleanup;

    int *per_layer = calloc((size_t)D, sizeof(int));
    int *sole_edge = malloc((size_t)D * sizeof(int));
    unsigned char *is_mandatory = calloc(edge_slots, sizeof(unsigned char));
    if (!per_layer || !sole_edge || !is_mandatory) {
        free(per_layer); free(sole_edge); free(is_mandatory);
        goto cleanup;
    }

    for (int e = 0; e < m; ++e) {
        int u = edges[e].from, v = edges[e].to;
        if (dist_s[u] >= 0 && dist_t[v] >= 0 &&
            (long long)dist_s[u] + 1 + dist_t[v] == D) {
            int k = dist_s[u];
            ++per_layer[k];
            sole_edge[k] = e;
        }
    }

    for (int k = 0; k < D; ++k) {
        if (per_layer[k] == 1) {
            is_mandatory[sole_edge[k]] = 1;
            ++result.count;
        }
    }

    if (result.count > 0) {
        result.indices = malloc((size_t)result.count * sizeof(int));
        if (!result.indices) {
            result.count = 0;
        } else {
            int j = 0;
            for (int e = 0; e < m; ++e)
                if (is_mandatory[e]) result.indices[j++] = e;
        }
    }

    free(per_layer);
    free(sole_edge);
    free(is_mandatory);
cleanup:
    free(forward_head);
    free(reverse_head);
    free(forward_next);
    free(reverse_next);
    free(dist_s);
    free(dist_t);
    free(queue);
    return result;
}

