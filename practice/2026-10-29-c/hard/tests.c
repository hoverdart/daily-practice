#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "solution.c"

static unsigned seed = 0x19ca2047u;
static unsigned rnd(void) { seed ^= seed << 13; seed ^= seed >> 17; seed ^= seed << 5; return seed; }
static long long brute(const Job *jobs, int n, int gap) {
    long long best = 0;
    for (unsigned mask = 0; mask < (1u << n); ++mask) {
        int valid = 1; long long reward = 0;
        for (int i = 0; i < n && valid; ++i) if (mask & (1u << i)) {
            reward += jobs[i].reward;
            for (int j = i+1; j < n; ++j) if (mask & (1u << j)) {
                if (!((long long)jobs[i].end + gap <= jobs[j].start ||
                      (long long)jobs[j].end + gap <= jobs[i].start)) {
                    valid = 0; break;
                }
            }
        }
        if (valid && reward > best) best = reward;
    }
    return best;
}
static void check(const Job *jobs, int n, int gap) {
    long long got = max_reward_with_cooldown(jobs,n,gap);
    long long want = brute(jobs,n,gap);
    assert(got == want);
}
int main(void) {
    assert(max_reward_with_cooldown(NULL,0,2) == 0);
    Job a[]={{0,2,5},{2,5,8},{5,7,9},{7,9,6}};
    check(a,4,0); check(a,4,1); check(a,4,3);
    Job b[]={{0,10,3},{0,10,11},{0,10,7}};
    check(b,3,0); check(b,3,100);
    Job c[]={{0,1,1000000000LL},{1000000000,1000000001,1000000000LL}};
    check(c,2,1000000000);
    Job d[]={{0,2,0},{1,3,0},{3,4,5}};
    check(d,3,0);
    for (int t=0;t<5000;++t) {
        Job j[11]; int n=(int)(rnd()%11u), gap=(int)(rnd()%9u);
        for (int i=0;i<n;++i) {
            int start=(int)(rnd()%28u), duration=1+(int)(rnd()%9u);
            j[i]=(Job){start,start+duration,(long long)(rnd()%41u)};
        }
        check(j,n,gap);
    }
    int n=200000; Job *big=malloc((size_t)n*sizeof *big); assert(big);
    for(int i=0;i<n;++i) big[i]=(Job){3*i,3*i+1,1000000000LL};
    assert(max_reward_with_cooldown(big,n,2)==200000000000000LL);
    for(int i=0;i<n;++i) big[i]=(Job){0,10,1000000000LL};
    assert(max_reward_with_cooldown(big,n,0)==1000000000LL);
    free(big);
    puts("hard: cooldown weighted scheduling passed");
    return 0;
}
