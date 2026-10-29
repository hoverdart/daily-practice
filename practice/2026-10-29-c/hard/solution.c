#include <stddef.h>

typedef struct { int start, end; long long reward; } Job;

/* Maximum reward of non-overlapping jobs separated by cooldown. */
long long max_reward_with_cooldown(const Job *jobs, int n, int cooldown) {
    (void)jobs; (void)n; (void)cooldown;
    /* TODO: copy+sort by end; binary-search predecessor; DP. */
    return 0;
}
