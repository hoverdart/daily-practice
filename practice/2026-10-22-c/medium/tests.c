#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "solution.c"

static unsigned rng = 0x123abcdeu;
static unsigned rnd(void) {
    rng ^= rng << 13; rng ^= rng >> 17; rng ^= rng << 5;
    return rng;
}
static Segment slow(const int *a, int n, int limit) {
    Segment best = {0,0};
    for (int l=0; l<n; ++l) {
        int lo=a[l], hi=a[l];
        for (int r=l; r<n; ++r) {
            if (a[r]<lo) lo=a[r];
            if (a[r]>hi) hi=a[r];
            if ((long long)hi-(long long)lo <= limit && r-l+1>best.length)
                best=(Segment){l,r-l+1};
        }
    }
    return best;
}
static void check(const int *a,int n,int limit) {
    Segment want=slow(a,n,limit),got=longest_stable_segment(a,n,limit);
    assert(want.start==got.start && want.length==got.length);
}
int main(void) {
    int a[]={8,2,4,7},b[]={5,5,5},c[]={4,1,4,1},d[]={INT_MIN,INT_MAX};
    check(NULL,0,0);check(a,4,4);check(b,3,0);check(c,4,2);check(d,2,0);
    for (int t=0;t<6000;++t) {
        int n=(int)(rnd()%65u), a[65];
        for(int i=0;i<n;++i) {
            unsigned x=rnd();
            a[i]=(x%19u==0u)?INT_MIN:(x%23u==0u)?INT_MAX:(int)(x%51u)-25;
        }
        int lim=(rnd()%4u==0u)?INT_MAX:(int)(rnd()%51u);
        check(a,n,lim);
    }
    int n=200000;
    int *large=malloc((size_t)n*sizeof *large);
    assert(large);
    for(int i=0;i<n;++i) large[i]=i%2?INT_MAX:INT_MIN;
    Segment got=longest_stable_segment(large,n,0);
    assert(got.start==0 && got.length==1);
    for(int i=0;i<n;++i) large[i]=42;
    got=longest_stable_segment(large,n,0);
    assert(got.start==0 && got.length==n);
    free(large);
    puts("medium: stable telemetry window passed");
    return 0;
}
