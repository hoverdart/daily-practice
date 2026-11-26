#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "solution.c"
static unsigned rng=24681357u;
static unsigned rnd(void) { rng ^= rng<<13; rng ^= rng>>17; rng ^= rng<<5; return rng; }
static void eq(Route a,Route b) {assert(a.cost==b.cost && a.hops==b.hops && a.ways==b.ways);}
/* Independent oracle: DP by exact hop count, up to n-1 (an optimal walk is simple). */
static Route brute(int n,const Edge *e,int m,int s,int t) {
    long long prev[12],cur[12];int pw[12],cw[12];assert(n<=12);
    for(int i=0;i<n;++i) {prev[i]=LLONG_MAX;pw[i]=0;}
    prev[s]=0;pw[s]=1;Route ans=s==t?(Route){0,0,1}:(Route){-1,-1,0};
    for(int h=1;h<n;++h) {
        for(int i=0;i<n;++i) {cur[i]=LLONG_MAX;cw[i]=0;}
        for(int j=0;j<m;++j) {
            int u=e[j].from,v=e[j].to;if(prev[u]==LLONG_MAX) continue;
            long long d=prev[u]+e[j].weight;
            if(d<cur[v]) {cur[v]=d;cw[v]=pw[u];}
            else if(d==cur[v]) cw[v]=(cw[v]+pw[u])%1000000007;
        }
        if(cur[t]!=LLONG_MAX && (ans.cost<0 || cur[t]<ans.cost)) ans=(Route){cur[t],h,cw[t]};
        for(int i=0;i<n;++i) {prev[i]=cur[i];pw[i]=cw[i];}
    }
    return ans;
}
static void check(int n,const Edge *e,int m,int s,int t) {eq(best_dispatch(n,e,m,s,t),brute(n,e,m,s,t));}
int main(void) {
    Edge a[]={{0,1,0},{0,1,0},{1,3,5},{0,2,2},{2,3,3},{0,3,5}},b[]={{0,1,0},{1,0,0},{1,1,0},{1,2,0},{0,2,1}},c[]={{0,1,1000000000},{1,2,1000000000},{2,3,1000000000}};
    check(4,a,6,0,3);check(4,a,5,0,3);check(3,b,5,0,2);check(4,c,3,0,3);check(4,c,3,3,0);check(1,NULL,0,0,0);check(2,NULL,0,0,1);
    for(int z=0;z<2000;++z) {
        Edge e[48];int n=1+(int)(rnd()%9),m=(int)(rnd()%49);
        for(int i=0;i<m;++i) e[i]=(Edge){(int)(rnd()%(unsigned)n),(int)(rnd()%(unsigned)n),(int)(rnd()%8)};
        check(n,e,m,(int)(rnd()%(unsigned)n),(int)(rnd()%(unsigned)n));
    }
    int n=100000,m=2*(n-1);Edge *e=malloc((size_t)m*sizeof *e);assert(e);
    int ways=1;for(int i=0;i<n-1;++i) {e[2*i]=e[2*i+1]=(Edge){i,i+1,1000000000};ways=(ways+ways)%1000000007;}
    eq(best_dispatch(n,e,m,0,n-1),(Route){(long long)(n-1)*1000000000,n-1,ways});
    free(e);puts("hard: passed 2000 randomized cases, edge and stress cases");
}
