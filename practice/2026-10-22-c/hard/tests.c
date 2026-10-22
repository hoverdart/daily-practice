#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "solution.c"

static int components(int n, const Edge *e, int m, int skip) {
    int seen[16]={0}, stack[16], total=0;
    for (int r=0;r<n;++r) if (!seen[r]) {
        ++total; int top=0; stack[top++]=r; seen[r]=1;
        while (top) {
            int u=stack[--top];
            for (int j=0;j<m;++j) if (j!=skip) {
                int v=e[j].u==u?e[j].v:e[j].v==u?e[j].u:-1;
                if (v>=0 && !seen[v]) { seen[v]=1; stack[top++]=v; }
            }
        }
    }
    return total;
}
static void check(int n,const Edge *e,int m) {
    int ids[40],count=find_critical_links(n,e,m,ids),expected=0;
    int base=components(n,e,m,-1);
    for (int j=0;j<m;++j) if (components(n,e,m,j)>base) {
        assert(expected<count && ids[expected]==j);
        ++expected;
    }
    assert(count==expected);
}
int main(void) {
    Edge triangle[]={{0,1},{1,2},{2,0},{2,3}};
    Edge parallel[]={{0,1},{0,1}};
    Edge disconnected[]={{0,1},{2,3}};
    Edge loops[]={{0,0},{0,1},{1,1},{1,2},{2,2}};
    check(4,triangle,4);check(2,parallel,2);
    check(5,disconnected,2);check(3,loops,5);check(1,NULL,0);
    unsigned state=17;
    for (int t=0;t<2000;++t) {
        state=state*1664525u+1013904223u;
        int n=1+(int)(state%12),m=(int)((state>>8)%30);
        Edge e[30];
        for (int i=0;i<m;++i) {
            state=state*1664525u+1013904223u;
            e[i].u=(int)(state%(unsigned)n);
            state=state*1664525u+1013904223u;
            e[i].v=(int)(state%(unsigned)n);
        }
        check(n,e,m);
    }
    int n=100000,m=n-1;
    Edge *path=malloc((size_t)m*sizeof *path);
    int *ids=malloc((size_t)m*sizeof *ids);
    assert(path && ids);
    for (int i=0;i<m;++i) path[i]=(Edge){i,i+1};
    assert(find_critical_links(n,path,m,ids)==m);
    for (int i=0;i<m;++i) assert(ids[i]==i);
    free(path);free(ids);
    puts("hard: critical relay links passed");
    return 0;
}
