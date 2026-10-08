#include <assert.h>
#include <stdio.h>
#include "solution.c"

static unsigned rng = 4125317u;
static unsigned next_rand(void) {
    rng ^= rng << 13; rng ^= rng >> 17; rng ^= rng << 5;
    return rng;
}

static int brute(const int *events, int n, const int *required, int r, int *start) {
    int need[256] = {0}, required_unique = 0;
    for (int i = 0; i < r; ++i)
        if (!need[required[i]]++) ++required_unique;
    if (required_unique == 0) { *start = 0; return 0; }
    int best = n + 1;
    *start = -1;
    for (int l = 0; l < n; ++l) {
        int seen[256] = {0}, remaining = required_unique;
        for (int rr = l; rr < n; ++rr) {
            int v = events[rr];
            if (need[v] && !seen[v]++) --remaining;
            if (remaining == 0) {
                if (rr - l + 1 < best) { best = rr - l + 1; *start = l; }
                break;
            }
        }
    }
    return best == n + 1 ? -1 : best;
}

int main(void) {
    int a[] = {9,2,9,4,2,7,4};
    int req[] = {2,4,7};
    int s = -10;
    assert(shortestAuditWindow(a, 7, req, 3, &s) == 3 && s == 3);
    int b[] = {2,4,7,2,4,7};
    assert(shortestAuditWindow(b, 6, req, 3, &s) == 3 && s == 0);
    int dup[] = {2,2,7};
    assert(shortestAuditWindow(a, 7, dup, 3, &s) == 2 && s == 4);
    int absent[] = {88};
    assert(shortestAuditWindow(a, 7, absent, 1, &s) == -1 && s == -1);
    assert(shortestAuditWindow(NULL, 0, req, 3, &s) == -1 && s == -1);
    assert(shortestAuditWindow(NULL, 0, NULL, 0, &s) == 0 && s == 0);
    int high[] = {255,0,255,0};
    int highreq[] = {0,255};
    assert(shortestAuditWindow(high, 4, highreq, 2, &s) == 2 && s == 0);

    for (int t = 0; t < 3000; ++t) {
        int events[16], wanted[10];
        int n = (int)(next_rand() % 16);
        int r = (int)(next_rand() % 10);
        for (int i = 0; i < n; ++i) events[i] = (int)(next_rand() % 9);
        for (int i = 0; i < r; ++i) wanted[i] = (int)(next_rand() % 9);
        int expected_start, actual_start;
        int expected = brute(events, n, wanted, r, &expected_start);
        int actual = shortestAuditWindow(events, n, wanted, r, &actual_start);
        assert(actual == expected && actual_start == expected_start);
    }
    puts("medium: sliding window tests passed");
    return 0;
}
