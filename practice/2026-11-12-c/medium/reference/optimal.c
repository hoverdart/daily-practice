#include <stddef.h>

typedef struct {
    int start;
    int length;
} DriftSpan;

static long long change_cost(int x, int y) {
    long long delta = (long long)x - (long long)y;
    return delta < 0 ? -delta : delta;
}

DriftSpan longest_drift_span(const int *readings, int n, long long budget) {
    DriftSpan best = {0, 0};
    int left = 0;
    long long drift = 0;

    for (int right = 0; right < n; ++right) {
        if (right > 0)
            drift += change_cost(readings[right], readings[right - 1]);

        while (drift > budget) {
            /* Remove the edge (left, left+1) as we drop left. */
            drift -= change_cost(readings[left + 1], readings[left]);
            ++left;
        }

        int length = right - left + 1;
        if (length > best.length ||
            (length == best.length && left < best.start)) {
            best.start = left;
            best.length = length;
        }
    }
    return best;
}

