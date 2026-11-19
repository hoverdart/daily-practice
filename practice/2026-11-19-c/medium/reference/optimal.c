#include <stdlib.h>

typedef struct {
    int start;
    int length;
} StableSpan;

StableSpan longest_stable_span(const int *readings, int n,
                               long long max_spread) {
    StableSpan best = {0, 0};
    if (n <= 0) return best;

    int *maxq = malloc((size_t)n * sizeof *maxq);
    int *minq = malloc((size_t)n * sizeof *minq);
    if (!maxq || !minq) {
        free(maxq);
        free(minq);
        return best; /* Allocation failure outside the input contract. */
    }

    int max_head = 0, max_tail = 0;
    int min_head = 0, min_tail = 0;
    int left = 0;

    for (int right = 0; right < n; ++right) {
        /* Decreasing values; front is the window maximum. */
        while (max_tail > max_head &&
               readings[maxq[max_tail - 1]] <= readings[right])
            --max_tail;
        maxq[max_tail++] = right;

        /* Increasing values; front is the window minimum. */
        while (min_tail > min_head &&
               readings[minq[min_tail - 1]] >= readings[right])
            --min_tail;
        minq[min_tail++] = right;

        while ((long long)readings[maxq[max_head]] -
               (long long)readings[minq[min_head]] > max_spread) {
            if (maxq[max_head] == left) ++max_head;
            if (minq[min_head] == left) ++min_head;
            ++left;
        }

        int length = right - left + 1;
        if (length > best.length ||
            (length == best.length && left < best.start)) {
            best.start = left;
            best.length = length;
        }
    }

    free(maxq);
    free(minq);
    return best;
}
