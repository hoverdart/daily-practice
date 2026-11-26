#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "solution.c"
static unsigned rng = 12345u;
static unsigned rnd(void) { rng ^= rng<<13; rng ^= rng>>17; rng ^= rng<<5; return rng; }
static void check(const int *a,int n,const int *lo,const int *hi,int q) {
    int out[32]; assert(q<=32);
    audit_counts(a,n,lo,hi,q,out);
    for(int j=0;j<q;++j) {
        int want=0;
        for(int i=0;i<n;++i) if(lo[j]<=a[i] && a[i]<=hi[j]) ++want;
        assert(out[j]==want);
    }
}
int main(void) {
    int a[]={INT_MIN,-3,2,2,8,INT_MAX}, lo[]={INT_MIN,2,0,9,8,INT_MAX}, hi[]={INT_MAX,2,8,1,8,INT_MAX};
    check(a,6,lo,hi,6); check(NULL,0,lo,hi,6); check(a,6,NULL,NULL,0);
    for(int t=0;t<1500;++t) {
        int b[64],l[32],h[32],n=(int)(rnd()%65),q=(int)(rnd()%33),v=-50;
        for(int i=0;i<n;++i) {v+=(int)(rnd()%4); b[i]=v;}
        for(int j=0;j<q;++j) {l[j]=(int)(rnd()%150)-70; h[j]=(int)(rnd()%150)-70;}
        check(b,n,l,h,q);
    }
    int n=200000; int *b=malloc((size_t)n*sizeof *b), *l=malloc((size_t)n*sizeof *l), *h=malloc((size_t)n*sizeof *h), *out=malloc((size_t)n*sizeof *out);
    assert(b&&l&&h&&out);
    for(int i=0;i<n;++i) {b[i]=i/2; l[i]=i/2; h[i]=i/2;}
    audit_counts(b,n,l,h,n,out);
    for(int i=0;i<n;++i) assert(out[i]==2);
    free(b);free(l);free(h);free(out); puts("easy: passed 1500 randomized cases, edge and stress cases");
}
