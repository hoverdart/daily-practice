#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "solution.c"

static unsigned rng = 0x73c2db11u;
static unsigned rnd(void) {
    rng ^= rng << 13; rng ^= rng >> 17; rng ^= rng << 5;
    return rng;
}
static int compare_ints(const void *px, const void *py) {
    int x = *(const int *)px, y = *(const int *)py;
    return (x > y) - (x < y);
}
/* Deliberately independent O(na*nb) oracle: count each distinct left ID
   by scanning both logs from scratch. */
static size_t oracle(const int *a, size_t na, const int *b, size_t nb,
                     size_t quota) {
    size_t result = 0;
    for (size_t i = 0; i < na; ++i) {
        int id = a[i];
        if (i && a[i - 1] == id) continue;
        size_t ca = 0, cb = 0;
        for (size_t j = 0; j < na; ++j) if (a[j] == id) ++ca;
        for (size_t j = 0; j < nb; ++j) if (b[j] == id) ++cb;
        size_t count = ca < cb ? ca : cb;
        result += count < quota ? count : quota;
    }
    return result;
}
static void check(const int *a, size_t na, const int *b, size_t nb,
                  size_t quota) {
    assert(count_capped_matches(a, na, b, nb, quota) ==
           oracle(a, na, b, nb, quota));
}
int main(void) {
    int a[] = {-2,-2,3,3,3,8};
    int b[] = {-2,-2,-2,3,3,7};
    assert(count_capped_matches(a,6,b,6,2) == 4);
    check(NULL,0,NULL,0,0);
    check(NULL,0,b,6,100);
    check(a,6,NULL,0,100);
    check(a,6,b,6,0);
    check(a,6,b,6,(size_t)-1);
    int extreme_a[] = {INT_MIN,INT_MIN,0,INT_MAX,INT_MAX};
    int extreme_b[] = {INT_MIN,0,0,INT_MAX};
    check(extreme_a,5,extreme_b,4,1);
    check(extreme_a,5,extreme_b,4,3);
    int disjoint_a[] = {4,5}, disjoint_b[] = {-2,-1};
    check(disjoint_a,2,disjoint_b,2,3);

    for (int t = 0; t < 7500; ++t) {
        int aa[70], bb[70];
        size_t na = rnd() % 70u, nb = rnd() % 70u;
        for (size_t i = 0; i < na; ++i) aa[i] = (int)(rnd()%23u)-11;
        for (size_t i = 0; i < nb; ++i) bb[i] = (int)(rnd()%23u)-11;
        qsort(aa,na,sizeof(int),compare_ints);
        qsort(bb,nb,sizeof(int),compare_ints);
        size_t quota = t%8 == 0 ? (size_t)-1 : rnd()%12u;
        check(aa,na,bb,nb,quota);
    }
    const size_t n = 200000;
    int *aa = malloc(n*sizeof(int));
    int *bb = malloc(n*sizeof(int));
    assert(aa && bb);
    for (size_t i=0; i<n; ++i) aa[i]=bb[i]=(int)(i/4);
    assert(count_capped_matches(aa,n,bb,n,1) == 50000);
    assert(count_capped_matches(aa,n,bb,n,3) == 150000);
    assert(count_capped_matches(aa,n,bb,n,(size_t)-1) == n);
    free(aa); free(bb);
    puts("easy: two-log replay quota passed");
    return 0;
}

