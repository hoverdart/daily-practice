#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include "solution.c"

static unsigned rng = 98765u;
static unsigned next_rand(void) {
    rng ^= rng << 13; rng ^= rng >> 17; rng ^= rng << 5;
    return rng;
}

/* Independent oracle: Bellman-Ford on the expanded (node,risk) graph. */
static long long brute(int n, int m, const Road *roads, int budget) {
    int stride = budget + 1;
    int states = n * stride;
    long long dist[1000];
    const long long INF = LLONG_MAX / 4;
    assert(states <= 1000);
    for (int i = 0; i < states; ++i) dist[i] = INF;
    dist[0] = 0;
    for (int pass = 0; pass < states - 1; ++pass) {
        int changed = 0;
        for (int i = 0; i < m; ++i) {
            Road r = roads[i];
            for (int spent = 0; spent + r.risk <= budget; ++spent) {
                int u = r.from * stride + spent;
                int v = r.to * stride + spent + r.risk;
                if (dist[u] != INF && dist[u] + r.time < dist[v]) {
                    dist[v] = dist[u] + r.time;
                    changed = 1;
                }
            }
        }
        if (!changed) break;
    }
    long long best = INF;
    for (int k = 0; k <= budget; ++k) {
        long long d = dist[(n - 1) * stride + k];
        if (d < best) best = d;
    }
    return best == INF ? -1 : best;
}

int main(void) {
    assert(fastestSafeRoute(1, 0, NULL, 0) == 0);
    assert(fastestSafeRoute(2, 0, NULL, 3) == -1);
    Road a[] = {{0,2,1,4},{0,1,4,1},{1,2,2,1}};
    assert(fastestSafeRoute(3, 3, a, 2) == 6);
    assert(fastestSafeRoute(3, 3, a, 4) == 1);
    Road b[] = {{0,1,7,0},{1,2,0,0},{0,2,9,0},{2,1,0,0}};
    assert(fastestSafeRoute(3, 4, b, 0) == 7);
    Road c[] = {{0,1,1000000000,0},{1,2,1000000000,0},
                {2,3,1000000000,0}};
    assert(fastestSafeRoute(4, 3, c, 0) == 3000000000LL);
    Road d[] = {{1,0,1,0}};
    assert(fastestSafeRoute(2, 1, d, 0) == -1);
    Road e[] = {{0,1,1,2},{1,2,1,2},{0,2,10,0}};
    assert(fastestSafeRoute(3, 3, e, 3) == 10);
    assert(fastestSafeRoute(3, 3, e, 4) == 2);

    for (int t = 0; t < 1200; ++t) {
        int n = 2 + (int)(next_rand() % 6);
        int budget = (int)(next_rand() % 6);
        int m = (int)(next_rand() % 25);
        Road roads[25];
        for (int i = 0; i < m; ++i) {
            roads[i] = (Road){(int)(next_rand() % (unsigned)n),
                              (int)(next_rand() % (unsigned)n),
                              (int)(next_rand() % 11),
                              (int)(next_rand() % 8)};
        }
        long long expected = brute(n, m, roads, budget);
        long long actual = fastestSafeRoute(n, m, roads, budget);
        assert(expected == actual);
    }
    puts("hard: budgeted Dijkstra tests passed");
    return 0;
}
