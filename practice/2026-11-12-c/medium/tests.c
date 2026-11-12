#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "solution.c"

static unsigned seed = 0xa9d31c20u;
static unsigned rnd(void) {
    seed ^= seed << 13; seed ^= seed >> 17; seed ^= seed << 5;
    return seed;
}
static long long brute_step(int a, int b) {
    long long d = (long long)a - (long long)b;
    return d < 0 ? -d : d;
}
/* Independent exhaustive O(n^2) oracle. */
static DriftSpan brute(const int *a, int n, long long budget) {
    DriftSpan best = {0,0};
    for (int l=0; l<n; ++l) {
        long long cost = 0;
        for (int r=l; r<n; ++r) {
            if (r>l) cost += brute_step(a[r],a[r-1]);
            int len = r-l+1;
            if (cost<=budget &&
                (len>best.length || (len==best.length && l<best.start))) {
                best.start=l;
                best.length=len;
            }
        }
    }
    return best;
}
static void check(const int *a, int n, long long budget) {
    DriftSpan got = longest_drift_span(a,n,budget);
    DriftSpan want = brute(a,n,budget);
    assert(got.start==want.start && got.length==want.length);
}
int main(void) {
    DriftSpan z=longest_drift_span(NULL,0,0);
    assert(z.start==0 && z.length==0);
    int a[]={4,8,7,15,13};
    DriftSpan x=longest_drift_span(a,5,5);
    assert(x.start==0 && x.length==3);
    int ties[]={4,3,2,1};
    x=longest_drift_span(ties,4,2);
    assert(x.start==0 && x.length==3);
    int eq[]={6,6,6,6};
    x=longest_drift_span(eq,4,0);
    assert(x.start==0 && x.length==4);
    int ext[]={INT_MIN,INT_MAX,INT_MIN};
    check(ext,3,0);
    x=longest_drift_span(ext,3,4294967295LL);
    assert(x.start==0 && x.length==2);
    check(ext,3,2LL*4294967295LL);
    check(ext,3,LLONG_MAX);

    for (int t=0; t<8500; ++t) {
        int arr[65];
        int n=(int)(rnd()%65u);
        for (int i=0; i<n; ++i) {
            unsigned v=rnd()%37u;
            arr[i]=v==0?INT_MIN : v==1?INT_MAX : (int)(rnd()%71u)-35;
        }
        long long budget=t%11==0 ? LLONG_MAX :
                         t%11==1 ? 0 : (long long)(rnd()%220u);
        check(arr,n,budget);
    }

    const int n=200000;
    int *huge=malloc((size_t)n*sizeof(int));
    assert(huge);
    for (int i=0; i<n; ++i) huge[i]=i&1?INT_MAX:INT_MIN;
    x=longest_drift_span(huge,n,0);
    assert(x.start==0 && x.length==1);
    x=longest_drift_span(huge,n,2LL*4294967295LL);
    assert(x.start==0 && x.length==3);
    x=longest_drift_span(huge,n,(long long)(n-1)*4294967295LL);
    assert(x.start==0 && x.length==n);
    for (int i=0; i<n; ++i) huge[i]=3;
    x=longest_drift_span(huge,n,0);
    assert(x.start==0 && x.length==n);
    free(huge);
    puts("medium: longest drift-controlled span passed");
    return 0;
}

