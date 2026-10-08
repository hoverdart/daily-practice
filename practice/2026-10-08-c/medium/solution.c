#include <limits.h>
#include <stddef.h>

/* Return shortest length; -1 if impossible. Set *start_out to start index
   (or -1 if impossible). If required_count == 0, return 0/start 0.
   Codes are in [0,255]; duplicate required codes count only once. */
int shortestAuditWindow(const int *events, int n,
                        const int *required, int required_count,
                        int *start_out) {
    (void)events; (void)n; (void)required; (void)required_count;
    *start_out = -1;
    /* TODO:
       - Build required-code flags (not a hash map).
       - Grow right pointer and count newly satisfied requirements.
       - While valid, record candidate and shrink from left.
       - Keep earliest start on equal-length windows. */
    return -1;
}
