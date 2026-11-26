#include <limits.h>
#include <stdlib.h>
typedef struct { int from,to,weight; } Edge;
typedef struct { long long cost; int hops,ways; } Route;
typedef struct { long long cost; int hops,v; } Ticket;
static int before(Ticket a,Ticket b) {return a.cost<b.cost || (a.cost==b.cost && a.hops<b.hops);}
static void push(Ticket *h,int *size,Ticket x) {
    int i=(*size)++;
    while(i>0) {int p=(i-1)/2;if(!before(x,h[p])) break;h[i]=h[p];i=p;}
    h[i]=x;
}
static Ticket pop(Ticket *h,int *size) {
    Ticket result=h[0],x=h[--*size];int i=0;
    while(2*i+1<*size) {
        int c=2*i+1;if(c+1<*size && before(h[c+1],h[c])) ++c;
        if(!before(h[c],x)) break;
        h[i]=h[c];i=c;
    }
    if(*size) h[i]=x;
    return result;
}
Route best_dispatch(int n,const Edge *edges,int m,int start,int target) {
    const int mod=1000000007;
    int *head=malloc((size_t)n*sizeof *head), *next=malloc((size_t)(m+1)*sizeof *next);
    Route *best=malloc((size_t)n*sizeof *best);
    Ticket *heap=malloc((size_t)(m+1)*sizeof *heap);
    if(!head||!next||!best||!heap) abort();
    for(int i=0;i<n;++i) {head[i]=-1;best[i]=(Route){LLONG_MAX,INT_MAX,0};}
    for(int i=0;i<m;++i) {int u=edges[i].from;next[i]=head[u];head[u]=i;}
    best[start]=(Route){0,0,1}; int size=0;push(heap,&size,(Ticket){0,0,start});
    while(size) {
        Ticket x=pop(heap,&size);int u=x.v;
        if(x.cost!=best[u].cost || x.hops!=best[u].hops) continue;
        if(u==target) break;
        for(int e=head[u];e!=-1;e=next[e]) {
            int v=edges[e].to;Ticket y={x.cost+edges[e].weight,x.hops+1,v};
            Ticket old={best[v].cost,best[v].hops,v};
            if(before(y,old)) {best[v]=(Route){y.cost,y.hops,best[u].ways};push(heap,&size,y);}
            else if(y.cost==old.cost && y.hops==old.hops) best[v].ways=(best[v].ways+best[u].ways)%mod;
        }
    }
    Route ans=best[target];if(ans.cost==LLONG_MAX) ans=(Route){-1,-1,0};
    free(head);free(next);free(best);free(heap);return ans;
}
