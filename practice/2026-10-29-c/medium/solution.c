#include <stddef.h>

typedef struct { int start; int length; } Window;

/* Shortest contiguous window with at least k distinct byte IDs. */
Window shortest_k_types(const unsigned char *events, int n, int k) {
    (void)events; (void)n; (void)k;
    /* TODO: frequency[256], distinct count, left/right pointers. */
    return (Window){-1, 0};
}
