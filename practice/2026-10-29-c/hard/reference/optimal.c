#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int start, end; long long reward; } Job;

static int by_end(const void *ap, const void *bp) {
    const Job *a = ap, *b = bp;
    if (a->end != b->end) return (a->end > b->end) - (a->end < b->end);
    return (a->start > b->start) - (a->start < b->start);
}

long long max_reward_with_cooldown(const Job *jobs, int n, int cooldown) {
    if (n <= 0) return 0;
    if (!jobs || cooldown < 0) return -1;
    Job *ordered = malloc((size_t)n * sizeof *ordered);
    long long *dp = calloc((size_t)n + 1, sizeof *dp);
    if (!ordered || !dp) { free(ordered); free(dp); return -1; }
    memcpy(ordered, jobs, (size_t)n * sizeof *ordered);
    qsort(ordered, (size_t)n, sizeof *ordered, by_end);
    for (int i = 0; i < n; ++i) {
        long long cutoff = (long long)ordered[i].start - cooldown;
        int lo = 0, hi = i;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if ((long long)ordered[mid].end <= cutoff) lo = mid + 1;
            else hi = mid;
        }
        long long take = ordered[i].reward + dp[lo];
        dp[i+1] = dp[i] > take ? dp[i] : take;
    }
    long long result = dp[n];
    free(dp); free(ordered);
    return result;
}
