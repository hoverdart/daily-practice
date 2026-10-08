#include <limits.h>
#include <stddef.h>

int shortestAuditWindow(const int *events, int n,
                        const int *required, int required_count,
                        int *start_out) {
    unsigned char needed[256] = {0};
    int freq[256] = {0};
    int missing = 0;
    for (int i = 0; i < required_count; ++i) {
        if (!needed[required[i]]) { needed[required[i]] = 1; ++missing; }
    }
    if (missing == 0) { *start_out = 0; return 0; }
    int left = 0, best = INT_MAX, best_start = -1;
    for (int right = 0; right < n; ++right) {
        int code = events[right];
        if (needed[code] && ++freq[code] == 1) --missing;
        while (missing == 0) {
            int len = right - left + 1;
            if (len < best) { best = len; best_start = left; }
            code = events[left++];
            if (needed[code] && --freq[code] == 0) ++missing;
        }
    }
    *start_out = best_start;
    return best == INT_MAX ? -1 : best;
}
