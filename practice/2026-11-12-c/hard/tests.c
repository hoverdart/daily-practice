#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "solution.c"

static unsigned seed = 0xba17e523u;
static unsigned rnd(void) {
    seed ^= seed << 13; seed ^= seed >> 17; seed ^= seed << 5;
    return seed;
}
/* Independent O(m(n+m)) oracle: count components after removing edge e.
   Used only on tiny graphs. */
static int components_without(int n, const Cable *edges, int m, int omit) {
    int seen[12] = {0}, queue[12], count = 0;
    for (int start=0; start<n; ++start) {
        if (seen[start]) continue;
        ++count;
        int front=0, back=0;
        seen[start]=1; queue[back++]=start;
        while (front<back) {
            int u=queue[front++];
            for (int e=0; e<m; ++e) {
                if (e==omit) continue;
                int v=-1;
                if (edges[e].u==u) v=edges[e].v;
                else if (edges[e].v==u) v=edges[e].u;
                if (v>=0 && !seen[v]) {
                    seen[v]=1; queue[back++]=v;
                }
            }
        }
    }
    return count;
}
static void check(int n, const Cable *edges, int m) {
    BridgeReport got=find_bridges(n,edges,m);
    if (m==0) {
        assert(got.flags==NULL && got.count==0);
        return;
    }
    assert(got.flags!=NULL);
    int initial=components_without(n,edges,m,-1), count=0;
    for (int e=0; e<m; ++e) {
        int expected=components_without(n,edges,m,e)>initial;
        assert(got.flags[e]==(unsigned char)expected);
        count+=expected;
    }
    assert(got.count==count);
    free(got.flags);
}
int main(void) {
    check(0,NULL,0);
    check(7,NULL,0);
    Cable cycle_tail[]={{0,1},{1,2},{2,0},{2,3}};
    check(4,cycle_tail,4);
    Cable parallel[]={{0,1},{0,1}};
    check(2,parallel,2);
    Cable loops[]={{0,0},{0,1},{1,2}};
    check(3,loops,3);
    Cable disconnected[]={{0,1},{1,2},{3,4}};
    check(6,disconnected,3);
    Cable complex[]={{0,1},{0,1},{1,2},{2,3},{3,1},{3,4},{4,4},{5,6},{6,5}};
    check(8,complex,9);

    for (int t=0; t<7000; ++t) {
        int n=(int)(rnd()%9u);
        int m=n==0?0:(int)(rnd()%27u);
        Cable edges[27];
        for (int e=0; e<m; ++e) {
            edges[e].u=(int)(rnd()%(unsigned)n);
            edges[e].v=(int)(rnd()%(unsigned)n);
        }
        check(n,edges,m);
    }

    const int n=150000;
    Cable *big=malloc((size_t)n*sizeof(Cable));
    assert(big);
    for (int e=0; e<n-1; ++e) {
        big[e].u=e; big[e].v=e+1;
    }
    BridgeReport got=find_bridges(n,big,n-1);
    assert(got.flags && got.count==n-1);
    for (int e=0; e<n-1; ++e) assert(got.flags[e]==1);
    free(got.flags);
    big[n-1].u=n-1; big[n-1].v=0; /* close the cycle */
    got=find_bridges(n,big,n);
    assert(got.flags && got.count==0);
    for (int e=0; e<n; ++e) assert(got.flags[e]==0);
    free(got.flags);
    free(big);
    puts("hard: low-link bridge detection passed");
    return 0;
}

