#include <stdlib.h>

typedef struct {
    int start;
    int length;
} StableSpan;

StableSpan longest_stable_span(const int *readings, int n,
                               long long max_spread) {
    /* TODO: allocate index arrays for decreasing-max and increasing-min
       deques; extend right, shrink left while max-min exceeds max_spread.
       Preserve the smallest start on ties and free all allocated arrays. */
    (void)readings;
    (void)n;
    (void)max_spread;
    StableSpan missing = {0, 0};
    return missing;
}
