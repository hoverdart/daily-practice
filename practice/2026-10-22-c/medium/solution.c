#include <stddef.h>

typedef struct { int start; int length; } Segment;

/* Longest contiguous window with max-min <= limit; earliest start on ties. */
Segment longest_stable_segment(const int *readings, int n, int limit) {
    (void)readings; (void)n; (void)limit;
    /* TODO: two monotonic index deques, left pointer, 64-bit range difference. */
    return (Segment){0, 0};
}
