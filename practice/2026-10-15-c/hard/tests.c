#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include "solution.c"

static unsigned state = 0x8a4b231fu;
static unsigned next_rand(void) {
    state ^= state << 13; state ^= state >> 17; state ^= state << 5;
    return state;
}
/* Independent Floyd-Warshall oracle, only for small graphs (n<=8). */
static int oracle(int n, const Edge *edges, int m,
                  int src, int dst, long long *out) {
    const long long INF = LLONG_MAX / 8;
    long long d[8][8];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) d[i][j] = i == j ? 0 : INF;
    for (int i = 0; i < m; ++i) {
        Edge e = edges[i];
        if (e.weight < d[e.from][e.to]) d[e.from][e.to] = e.weight;
    }
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (d[i][k] != INF && d[k][j] != INF &&
                    d[i][k] + d[k][j] < d[i][j])
                    d[i][j] = d[i][k] + d[k][j];
    for (int k = 0; k < n; ++k)
        if (d[src][k] != INF && d[k][k] < 0 && d[k][dst] != INF)
            return 1;
    if (d[src][dst] == INF) return -1;
    *out = d[src][dst];
    return 0;
}
static void check(int n, const Edge *edges, int m, int src, int dst) {
    long long got_cost = 123456789, want_cost = 0;
    int got = cheapest_rebate_route(n, edges, m, src, dst, &got_cost);
    int want = oracle(n, edges, m, src, dst, &want_cost);
    assert(got == want);
    if (got == 0) assert(got_cost == want_cost);
    else assert(got_cost == 123456789); /* output untouched on failure */
}
int main(void) {
    Edge finite[] = {{0,1,5},{1,2,-7},{0,2,3}};
    check(3, finite, 3, 0, 2);
    Edge cycle[] = {{0,1,1},{1,2,-4},{2,1,1},{2,3,2}};
    check(4, cycle, 4, 0, 3);
    Edge irrelevant[] = {{0,1,1},{1,2,-4},{2,1,1},{0,3,9}};
    check(4, irrelevant, 4, 0, 3);
    Edge unreachable[] = {{1,2,-3},{2,1,1}};
    check(4, unreachable, 2, 0, 3);
    Edge self[] = {{0,0,-1}}; check(1, self, 1, 0, 0);
    check(1, self, 0, 0, 0);
    for (int t = 0; t < 2500; ++t) {
        int n = 1 + (int)(next_rand() % 7), m = (int)(next_rand() % 40);
        Edge edges[40];
        for (int i = 0; i < m; ++i) {
            edges[i].from = (int)(next_rand() % (unsigned)n);
            edges[i].to = (int)(next_rand() % (unsigned)n);
            edges[i].weight = (int)(next_rand() % 15) - 7;
        }
        check(n, edges, m, (int)(next_rand() % (unsigned)n),
              (int)(next_rand() % (unsigned)n));
    }
    Edge chain[199];
    for (int i = 0; i < 199; ++i) chain[i] = (Edge){i,i+1,-1000000};
    long long cost = 0;
    assert(cheapest_rebate_route(200, chain, 199, 0, 199, &cost) == 0);
    assert(cost == -199000000LL);
    puts("hard: rebate Bellman-Ford passed");
    return 0;
}
