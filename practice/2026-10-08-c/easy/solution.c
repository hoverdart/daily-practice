#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int *items;
    size_t capacity;
    size_t head;
    size_t size;
} Ring;

/* Return 1 on success, 0 on invalid capacity/allocation failure. */
int ring_init(Ring *r, size_t capacity) {
    (void)r; (void)capacity;
    /* TODO: allocate capacity ints; initialize all fields. */
    return 0;
}

void ring_destroy(Ring *r) {
    (void)r;
    /* TODO: free storage and reset fields. */
}

/* Return 0 if full, otherwise append value and return 1. */
int ring_push(Ring *r, int value) {
    (void)r; (void)value;
    /* TODO: compute tail from head and size with modulo. */
    return 0;
}

/* Return 0 if empty (do not write *out), otherwise remove oldest item. */
int ring_pop(Ring *r, int *out) {
    (void)r; (void)out;
    /* TODO: advance head and reduce size. */
    return 0;
}

/* Return 0 if empty, otherwise copy oldest item to *out. */
int ring_front(const Ring *r, int *out) {
    (void)r; (void)out;
    /* TODO: read head without removing. */
    return 0;
}
