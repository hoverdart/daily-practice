#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "solution.c"

static unsigned rng = 0x0d46be3du;
static unsigned next_rand(void) {
    rng ^= rng << 13;
    rng ^= rng >> 17;
    rng ^= rng << 5;
    return rng;
}

static StableSpan brute(const int *a, int n, long long spread) {
    StableSpan best = {0,0};
    for (int l = 0; l < n; ++l) {
        int lo = INT_MAX, hi = INT_MIN;
        for (int r = l; r < n; ++r) {
            if (a[r] < lo) lo = a[r];
            if (a[r] > hi) hi = a[r];
            int length = r - l + 1;
            if ((long long)hi - (long long)lo <= spread &&
                (length > best.length ||
                 (length == best.length && l < best.start))) {
                best.start = l;
                best.length = length;
            }
        }
    }
    return best;
}

static void check(const int *a, int n, long long spread) {
    StableSpan want = brute(a, n, spread);
    StableSpan got = longest_stable_span(a, n, spread);
    assert(got.start == want.start && got.length == want.length);
}

int main(void) {
    check(NULL, 0, 0);
    int a[] = {3,8,7,11,5};
    check(a, 5, 4);
    int b[] = {1,2,3,4};
    check(b, 4, 1);
    int c[] = {7,7,7};
    check(c, 3, 0);
    int d[] = {INT_MIN,INT_MAX,INT_MIN,INT_MAX};
    check(d, 4, 0);
    check(d, 4, 4294967295LL);
    int e[] = {-1,100,-1,100,-1};
    check(e, 5, 99);

    for (int t = 0; t < 8500; ++t) {
        int values[70];
        int n = (int)(next_rand() % 70u);
        for (int i = 0; i < n; ++i) {
            unsigned pick = next_rand() % 23u;
            values[i] = pick == 0 ? INT_MIN :
                        pick == 1 ? INT_MAX :
                        (int)(next_rand() % 71u) - 35;
        }
        long long budget = t % 11 == 0 ? 4294967295LL :
                           t % 11 == 1 ? 0 :
                           (long long)(next_rand() % 200u);
        check(values, n, budget);
    }

    const int n = 200000;
    int *huge = malloc((size_t)n * sizeof *huge);
    assert(huge);
    for (int i = 0; i < n; ++i) huge[i] = (i & 1) ? INT_MAX : INT_MIN;
    StableSpan got = longest_stable_span(huge, n, 0);
    assert(got.start == 0 && got.length == 1);
    got = longest_stable_span(huge, n, 4294967295LL);
    assert(got.start == 0 && got.length == n);
    for (int i = 0; i < n; ++i) huge[i] = i;
    got = longest_stable_span(huge, n, 100);
    assert(got.start == 0 && got.length == 101);
    free(huge);
    puts("medium: stable sensor window passed");
    return 0;
}
