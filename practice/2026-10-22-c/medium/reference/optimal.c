#include <stddef.h>
#include <stdlib.h>

typedef struct { int start; int length; } Segment;

Segment longest_stable_segment(const int *readings, int n, int limit) {
    Segment best = {0, 0};
    if (n <= 0) return best;
    int *maxq = malloc((size_t)n * sizeof *maxq);
    int *minq = malloc((size_t)n * sizeof *minq);
    if (!maxq || !minq) { free(maxq); free(minq); return best; }
    int max_head = 0, max_tail = 0, min_head = 0, min_tail = 0, left = 0;
    for (int right = 0; right < n; ++right) {
        while (max_head < max_tail && readings[maxq[max_tail - 1]] <= readings[right])
            --max_tail;
        maxq[max_tail++] = right;
        while (min_head < min_tail && readings[minq[min_tail - 1]] >= readings[right])
            --min_tail;
        minq[min_tail++] = right;
        while (max_head < max_tail && min_head < min_tail &&
               (long long)readings[maxq[max_head]] - (long long)readings[minq[min_head]] > limit) {
            if (maxq[max_head] == left) ++max_head;
            if (minq[min_head] == left) ++min_head;
            ++left;
        }
        int len = right - left + 1;
        if (len > best.length) best = (Segment){left, len};
    }
    free(maxq);
    free(minq);
    return best;
}
