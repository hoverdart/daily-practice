#include <stddef.h>

/* Return the maximum number of pairs, up to quota per distinct event ID.
   Both inputs are sorted; do not change them. */
size_t count_capped_matches(const int *a, size_t na,
                            const int *b, size_t nb,
                            size_t quota) {
    (void)a;
    (void)na;
    (void)b;
    (void)nb;
    (void)quota;
    /* TODO: merge the two sorted streams, counting equal-value runs. */
    return 0;
}

