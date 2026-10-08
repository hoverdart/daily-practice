#include <limits.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct { int from, to, time, risk; } Road;
typedef struct { long long time; int state; } HeapNode;

/* Binary min-heap with 1-based indexing. Capacity is bounded by the
   number of possible successful edge relaxations plus the initial push. */
static void heap_push(HeapNode *heap, size_t *size, HeapNode item) {
    size_t i = ++*size;
    while (i > 1 && heap[i / 2].time > item.time) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = item;
}

static HeapNode heap_pop(HeapNode *heap, size_t *size) {
    HeapNode result = heap[1], last = heap[(*size)--];
    if (*size == 0) return result;
    size_t i = 1;
    while (2 * i <= *size) {
        size_t child = 2 * i;
        if (child + 1 <= *size && heap[child + 1].time < heap[child].time)
            ++child;
        if (heap[child].time >= last.time) break;
        heap[i] = heap[child];
        i = child;
    }
    heap[i] = last;
    return result;
}

long long fastestSafeRoute(int n, int m, const Road *roads, int budget) {
    if (n <= 0 || m < 0 || budget < 0) return -1;
    int stride = budget + 1;
    size_t states = (size_t)n * (size_t)stride;
    size_t max_pushes = 1 + (size_t)m * (size_t)stride;
    int *head = malloc((size_t)n * sizeof(int));
    int *next = malloc((size_t)(m ? m : 1) * sizeof(int));
    long long *dist = malloc(states * sizeof(long long));
    HeapNode *heap = malloc((max_pushes + 1) * sizeof(HeapNode));
    if (!head || !next || !dist || !heap) {
        free(head); free(next); free(dist); free(heap);
        return -1;
    }
    for (int i = 0; i < n; ++i) head[i] = -1;
    for (int i = 0; i < m; ++i) {
        next[i] = head[roads[i].from];
        head[roads[i].from] = i;
    }
    const long long INF = LLONG_MAX / 4;
    for (size_t i = 0; i < states; ++i) dist[i] = INF;
    dist[0] = 0;
    size_t heap_size = 0;
    heap_push(heap, &heap_size, (HeapNode){0, 0});
    long long answer = -1;
    while (heap_size > 0) {
        HeapNode cur = heap_pop(heap, &heap_size);
        int u = cur.state / stride, spent = cur.state % stride;
        if (cur.time != dist[cur.state]) continue;
        if (u == n - 1) { answer = cur.time; break; }
        for (int e = head[u]; e != -1; e = next[e]) {
            const Road *road = &roads[e];
            if (road->risk > budget - spent) continue;
            int next_state = road->to * stride + spent + road->risk;
            long long candidate = cur.time + road->time;
            if (candidate < dist[next_state]) {
                dist[next_state] = candidate;
                heap_push(heap, &heap_size, (HeapNode){candidate, next_state});
            }
        }
    }
    free(head); free(next); free(dist); free(heap);
    return answer;
}
