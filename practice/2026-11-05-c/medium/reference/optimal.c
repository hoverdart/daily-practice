#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

long long count_calm_intervals(const int *readings, int n, int tolerance) {
    if (n <= 0) return 0;
    int *maxq = malloc((size_t)n * sizeof(*maxq));
    int *minq = malloc((size_t)n * sizeof(*minq));
    if (!maxq || !minq) {
        free(maxq);
        free(minq);
        return -1; /* Memory allocation failure, never a legal interval count. */
    }

    int max_head = 0, max_tail = 0;
    int min_head = 0, min_tail = 0;
    int left = 0;
    long long answer = 0;

    for (int right = 0; right < n; ++right) {
        while (max_tail > max_head && readings[maxq[max_tail - 1]] <= readings[right])
            --max_tail;
        maxq[max_tail++] = right;

        while (min_tail > min_head && readings[minq[min_tail - 1]] >= readings[right])
            --min_tail;
        minq[min_tail++] = right;

        while ((int64_t)readings[maxq[max_head]] -
                   (int64_t)readings[minq[min_head]] > (int64_t)tolerance) {
            if (maxq[max_head] == left) ++max_head;
            if (minq[min_head] == left) ++min_head;
            ++left;
        }
        answer += (long long)(right - left + 1);
    }

    free(maxq);
    free(minq);
    return answer;
}

