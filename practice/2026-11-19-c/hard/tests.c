#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solution.c"

static unsigned rng = 0x7f10aa41u;
static unsigned next_rand(void) {
    rng ^= rng << 13;
    rng ^= rng >> 17;
    rng ^= rng << 5;
    return rng;
}

/* Independent O(states^2) Dijkstra oracle for small grids.
   This intentionally does NOT use 0-1 BFS or a deque. */
static int brute(const char *const *g, int rows, int cols) {
    if (rows <= 0 || cols <= 0 ||
        g[0][0] == '#' || g[rows-1][cols-1] == '#') return -1;
    int n = rows * cols * 4;
    assert(n <= 128);
    int dist[128], used[128] = {0};
    for (int i = 0; i < n; ++i) dist[i] = INT_MAX / 4;
    for (int d = 0; d < 4; ++d) dist[d] = 0;
    const int dr[4] = {-1,1,0,0}, dc[4] = {0,0,-1,1};
    for (int step = 0; step < n; ++step) {
        int u = -1;
        for (int i = 0; i < n; ++i)
            if (!used[i] && (u == -1 || dist[i] < dist[u])) u = i;
        if (u == -1 || dist[u] == INT_MAX/4) break;
        used[u] = 1;
        int r = (u/4)/cols, c = (u/4)%cols, previous = u%4;
        for (int d = 0; d < 4; ++d) {
            int nr = r+dr[d], nc = c+dc[d];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols ||
                g[nr][nc] == '#') continue;
            int v = (nr*cols+nc)*4+d;
            int cand = dist[u] + (d != previous);
            if (cand < dist[v]) dist[v] = cand;
        }
    }
    int best = INT_MAX/4;
    int target = ((rows-1)*cols + (cols-1))*4;
    for (int d = 0; d < 4; ++d)
        if (dist[target+d] < best) best = dist[target+d];
    return best == INT_MAX/4 ? -1 : best;
}

static void check(const char *const *g, int rows, int cols) {
    int expected = brute(g, rows, cols);
    int actual = min_relay_turns(g, rows, cols);
    assert(actual == expected);
}

int main(void) {
    assert(min_relay_turns(NULL,0,0) == -1);
    const char *one[] = {"."};
    const char *blocked[] = {"#"};
    const char *straight[] = {"..."};
    const char *square[] = {"..",".."};
    const char *forced[] = {"..#", "#..", "##."};
    const char *cutoff[] = {".#","##"};
    check(one,1,1);
    check(blocked,1,1);
    check(straight,1,3);
    check(square,2,2);
    check(forced,3,3);
    check(cutoff,2,2);
    assert(min_relay_turns(forced,3,3) == 3);

    for (int t = 0; t < 2500; ++t) {
        int rows = (int)(next_rand()%5u)+1;
        int cols = (int)(next_rand()%5u)+1;
        char storage[5][6] = {{0}};
        const char *g[5];
        for (int r = 0; r < rows; ++r) {
            g[r] = storage[r];
            for (int c = 0; c < cols; ++c)
                storage[r][c] = (next_rand()%5u == 0) ? '#' : '.';
        }
        check(g, rows, cols);
    }

    const int len = 200000;
    char *corridor = malloc((size_t)len + 1);
    assert(corridor);
    memset(corridor,'.',(size_t)len);
    corridor[len] = '\0';
    const char *long_grid[] = {corridor};
    assert(min_relay_turns(long_grid,1,len) == 0);
    corridor[len/2] = '#';
    assert(min_relay_turns(long_grid,1,len) == -1);
    free(corridor);

    const int side = 400; /* 160k cells */
    char **block = malloc((size_t)side * sizeof *block);
    assert(block);
    for (int r = 0; r < side; ++r) {
        block[r] = malloc((size_t)side + 1);
        assert(block[r]);
        memset(block[r],'.',(size_t)side);
        block[r][side] = '\0';
    }
    assert(min_relay_turns((const char *const *)block,side,side) == 1);
    for (int r = 0; r < side; ++r) free(block[r]);
    free(block);
    puts("hard: grid relay 0-1 BFS passed");
    return 0;
}
