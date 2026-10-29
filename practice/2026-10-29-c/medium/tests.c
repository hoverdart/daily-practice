#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "solution.c"

static unsigned seed = 0xf1c25a31u;
static unsigned rnd(void) { seed ^= seed << 13; seed ^= seed >> 17; seed ^= seed << 5; return seed; }
static Window slow(const unsigned char *a, int n, int k) {
    if (k == 0) return (Window){0,0};
    Window best = {-1,0};
    for (int l = 0; l < n; ++l) {
        unsigned char seen[256] = {0}; int distinct = 0;
        for (int r = l; r < n; ++r) {
            if (!seen[a[r]]) { seen[a[r]] = 1; ++distinct; }
            if (distinct >= k) {
                int len = r - l + 1;
                if (best.start == -1 || len < best.length) best = (Window){l,len};
                break;
            }
        }
    }
    return best;
}
static void check(const unsigned char *a, int n, int k) {
    Window got = shortest_k_types(a,n,k), want = slow(a,n,k);
    assert(got.start == want.start && got.length == want.length);
}
int main(void) {
    unsigned char a[] = {4,4,9,4,8,9}, b[] = {0,255,0,255}, c[] = {7,7,7};
    check(NULL,0,0); check(NULL,0,1); check(a,6,0); check(a,6,1);
    check(a,6,2); check(a,6,3); check(a,6,4); check(b,4,2);
    check(c,3,1); check(c,3,2); check(b,4,256);
    for (int t = 0; t < 7500; ++t) {
        unsigned char v[65]; int n = (int)(rnd()%65u);
        for (int i = 0; i < n; ++i) v[i] = (unsigned char)(rnd()%12u == 0 ? 255u : rnd()%9u);
        int k = (int)(rnd()%14u);
        check(v,n,k);
    }
    int n = 200000;
    unsigned char *big = malloc((size_t)n); assert(big);
    for (int i=0;i<n;++i) big[i]=(unsigned char)(i%256);
    Window got=shortest_k_types(big,n,256);
    assert(got.start==0 && got.length==256);
    got=shortest_k_types(big,n,1);
    assert(got.start==0 && got.length==1);
    free(big);
    puts("medium: shortest distinct-coverage window passed");
    return 0;
}
