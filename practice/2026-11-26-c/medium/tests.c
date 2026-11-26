#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "solution.c"
static unsigned rng=98765u;
static unsigned rnd(void) { rng ^= rng<<13; rng ^= rng>>17; rng ^= rng<<5; return rng; }
static long long brute(const int *a,int n,int u,int k) {
    long long ans=0;
    int *f=calloc((size_t)u,sizeof *f); assert(f);
    for(int l=0;l<n;++l) for(int r=l;r<n;++r) {
        for(int v=0;v<u;++v) f[v]=0;
        for(int i=l;i<=r;++i) ++f[a[i]];
        int rep=0; for(int v=0;v<u;++v) if(f[v]>=2) ++rep;
        if(rep<=k) ++ans;
    }
    free(f);return ans;
}
static void check(const int *a,int n,int u,int k) {assert(repeated_windows(a,n,u,k)==brute(a,n,u,k));}
int main(void) {
    int a[]={0,0,1,1},b[]={0,0,0},c[]={0,1,2,0,2,1,0};
    check(NULL,0,1,0); check(a,4,2,1); check(b,3,1,0); check(b,3,1,1); check(c,7,3,0); check(c,7,3,2);
    for(int t=0;t<1800;++t) {
        int x[28],n=(int)(rnd()%29),u=1+(int)(rnd()%12),k=(int)(rnd()%(unsigned)(u+1));
        for(int i=0;i<n;++i) x[i]=(int)(rnd()%(unsigned)u);
        check(x,n,u,k);
    }
    int n=200000; int *x=calloc((size_t)n,sizeof *x); assert(x);
    assert(repeated_windows(x,n,1,0)==n);
    assert(repeated_windows(x,n,1,1)==(long long)n*(n+1)/2);
    for(int i=0;i<n;++i) x[i]=i;
    assert(repeated_windows(x,n,n,0)==(long long)n*(n+1)/2);
    free(x); puts("medium: passed 1800 randomized cases, edge and stress cases");
}
