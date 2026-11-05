#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "solution.c"

static unsigned seed = 0xdec01241u;
static unsigned rnd(void) {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}

static long long slow(const int *a, int n, int tolerance) {
    long long answer = 0;
    for (int l = 0; l < n; ++l) {
        int low = a[l], high = a[l];
        for (int r = l; r < n; ++r) {
            if (a[r] < low) low = a[r];
            if (a[r] > high) high = a[r];
            if ((int64_t)high - (int64_t)low <= tolerance) ++answer;
        }
    }
    return answer;
}

static void check(const int *a, int n, int limit) {
    assert(count_calm_intervals(a,n,limit) == slow(a,n,limit));
}

int main(void) {
    int a[] = {4,1,3}, b[] = {2,2,2};
    int extremes[] = {INT_MIN,INT_MAX,INT_MIN,INT_MAX};
    check(NULL,0,0);
    check(a,3,2); assert(count_calm_intervals(a,3,2)==4);
    check(b,3,0); assert(count_calm_intervals(b,3,0)==6);
    check(extremes,4,INT_MAX);
    check(extremes,4,0);
    check(a,3,INT_MAX);
    int one = INT_MIN;
    check(&one,1,0);
    for (int t = 0; t < 9500; ++t) {
        int v[85];
        int n = (int)(rnd()%85u);
        int limit = (int)(rnd()%70u);
        for (int i = 0; i < n; ++i) {
            unsigned x = rnd()%19u;
            v[i] = x==0 ? INT_MIN : x==1 ? INT_MAX : (int)(rnd()%101u)-50;
        }
        check(v,n,limit);
    }
    int n=200000;
    int *large=malloc((size_t)n*sizeof(*large)); assert(large);
    for (int i=0;i<n;++i) large[i]=7;
    assert(count_calm_intervals(large,n,0)==(long long)n*(n+1)/2);
    for (int i=0;i<n;++i) large[i]=i%2 ? INT_MAX : INT_MIN;
    assert(count_calm_intervals(large,n,INT_MAX)==n);
    free(large);
    puts("medium: calm-interval counting passed");
    return 0;
}

