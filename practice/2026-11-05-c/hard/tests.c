#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "solution.c"

static unsigned seed = 0x69ca517bu;
static unsigned rnd(void) {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}

/* Independent brute-force oracle: scan all edges for BFS neighbors. */
static int slow_distance(int n, const DirectedEdge *edges, int m,
                         int source, int target, int banned) {
    int *dist = malloc((size_t)n * sizeof(int));
    int *queue = malloc((size_t)n * sizeof(int));
    assert(dist && queue);
    for (int i = 0; i < n; ++i) dist[i] = -1;
    int front = 0, back = 0;
    dist[source] = 0; queue[back++] = source;
    while (front < back) {
        int u = queue[front++];
        for (int e = 0; e < m; ++e) {
            if (e == banned || edges[e].from != u) continue;
            int v = edges[e].to;
            if (dist[v] < 0) {
                dist[v] = dist[u] + 1;
                queue[back++] = v;
            }
        }
    }
    int answer = dist[target];
    free(dist); free(queue);
    return answer;
}

static void check(int n, const DirectedEdge *edges, int m, int s, int t) {
    int base = slow_distance(n,edges,m,s,t,-1);
    int *want = malloc((size_t)(m>0?m:1)*sizeof(int));
    assert(want);
    int length = 0;
    if (base >= 0) {
        for (int e = 0; e < m; ++e) {
            int without = slow_distance(n,edges,m,s,t,e);
            if (without == -1 || without > base) want[length++] = e;
        }
    }
    MandatoryEdges got = mandatory_fastest_links(n,edges,m,s,t);
    assert(got.count == length);
    for (int i = 0; i < length; ++i)
        assert(got.indices != NULL && got.indices[i] == want[i]);
    free(got.indices);
    free(want);
}

int main(void) {
    DirectedEdge a[] = {{0,1},{1,3},{0,2},{2,3},{3,4}};
    DirectedEdge b[] = {{0,1},{0,1},{1,2}};
    DirectedEdge c[] = {{0,0},{0,1},{1,1},{1,2},{0,2}};
    check(5,a,5,0,4); check(3,b,3,0,2); check(3,c,5,0,2);
    MandatoryEdges ans = mandatory_fastest_links(5,a,5,0,4);
    assert(ans.count == 1 && ans.indices[0] == 4); free(ans.indices);
    ans = mandatory_fastest_links(3,b,3,0,2);
    assert(ans.count == 1 && ans.indices[0] == 2); free(ans.indices);
    check(1,NULL,0,0,0);
    check(3,NULL,0,0,2);
    check(5,a,5,4,0);
    for (int trial = 0; trial < 6500; ++trial) {
        int n = 1 + (int)(rnd()%9u);
        int m = (int)(rnd()%30u);
        DirectedEdge edges[30];
        for (int i = 0; i < m; ++i) {
            edges[i].from = (int)(rnd()%(unsigned)n);
            edges[i].to = (int)(rnd()%(unsigned)n);
        }
        int s = (int)(rnd()%(unsigned)n);
        int t = (int)(rnd()%(unsigned)n);
        check(n,edges,m,s,t);
    }
    const int n = 150000;
    DirectedEdge *chain = malloc((size_t)(n-1)*sizeof(*chain));
    assert(chain);
    for (int i = 0; i < n-1; ++i) chain[i] = (DirectedEdge){i,i+1};
    ans = mandatory_fastest_links(n,chain,n-1,0,n-1);
    assert(ans.count == n-1);
    for (int i = 0; i < n-1; ++i) assert(ans.indices[i] == i);
    free(ans.indices);
    free(chain);
    puts("hard: mandatory shortest-route edges passed");
    return 0;
}

