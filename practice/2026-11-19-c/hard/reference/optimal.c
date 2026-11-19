#include <limits.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
    int state;
    int distance;
} RelayTicket;

typedef struct {
    RelayTicket *data;
    size_t cap, head, size;
} RelayDeque;

/* Grow while preserving logical front-to-back order. */
static int relay_grow(RelayDeque *q) {
    size_t next_cap = q->cap ? q->cap * 2 : 32;
    RelayTicket *copy = malloc(next_cap * sizeof *copy);
    if (!copy) return 0;
    for (size_t i = 0; i < q->size; ++i)
        copy[i] = q->data[(q->head + i) % q->cap];
    free(q->data);
    q->data = copy;
    q->cap = next_cap;
    q->head = 0;
    return 1;
}

static int relay_push(RelayDeque *q, RelayTicket x, int front) {
    if (q->size == q->cap && !relay_grow(q)) return 0;
    if (front) {
        q->head = (q->head + q->cap - 1) % q->cap;
        q->data[q->head] = x;
    } else {
        size_t at = (q->head + q->size) % q->cap;
        q->data[at] = x;
    }
    ++q->size;
    return 1;
}

static RelayTicket relay_pop(RelayDeque *q) {
    RelayTicket x = q->data[q->head];
    q->head = (q->head + 1) % q->cap;
    --q->size;
    return x;
}

int min_relay_turns(const char *const *grid, int rows, int cols) {
    if (!grid || rows <= 0 || cols <= 0) return -1;
    if (grid[0][0] == '#' || grid[rows - 1][cols - 1] == '#')
        return -1;

    size_t count = (size_t)rows * (size_t)cols * 4;
    int *dist = malloc(count * sizeof *dist);
    if (!dist) return -1;
    for (size_t i = 0; i < count; ++i) dist[i] = INT_MAX;

    RelayDeque q = {NULL, 0, 0, 0};
    for (int direction = 0; direction < 4; ++direction) {
        dist[direction] = 0;
        if (!relay_push(&q, (RelayTicket){direction, 0}, 0))
            goto failure;
    }

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    while (q.size) {
        RelayTicket ticket = relay_pop(&q);
        int state = ticket.state;
        if (ticket.distance != dist[state]) continue;
        int cell = state / 4;
        int direction = state % 4;
        int r = cell / cols, c = cell % cols;
        if (r == rows - 1 && c == cols - 1) {
            int result = ticket.distance;
            free(q.data);
            free(dist);
            return result;
        }

        for (int next_dir = 0; next_dir < 4; ++next_dir) {
            int nr = r + dr[next_dir], nc = c + dc[next_dir];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols ||
                grid[nr][nc] == '#') continue;
            int next_state = (nr * cols + nc) * 4 + next_dir;
            int edge_cost = (direction == next_dir) ? 0 : 1;
            int candidate = ticket.distance + edge_cost;
            if (candidate >= dist[next_state]) continue;
            dist[next_state] = candidate;
            if (!relay_push(&q, (RelayTicket){next_state, candidate},
                            edge_cost == 0))
                goto failure;
        }
    }

    free(q.data);
    free(dist);
    return -1;

failure:
    free(q.data);
    free(dist);
    return -1; /* allocation failure */
}
