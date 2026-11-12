#include <stddef.h>

typedef struct {
    int start;
    int length;
} DriftSpan;

/* Longest span with adjacent-change total <= budget.
   Break ties by smaller start; n=0 returns {0,0}. */
DriftSpan longest_drift_span(const int *readings, int n, long long budget) {
    (void)readings;
    (void)n;
    (void)budget;
    /* TODO: O(n) variable window; cast to long long BEFORE subtraction. */
    DriftSpan answer = {0, 0};
    return answer;
}

