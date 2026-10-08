#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int *items;
    size_t capacity;
    size_t head;
    size_t size;
} Ring;

int ring_init(Ring *r, size_t capacity) {
    if (r == NULL || capacity == 0 || capacity > SIZE_MAX / sizeof(int)) return 0;
    int *items = malloc(capacity * sizeof(int));
    if (items == NULL) return 0;
    *r = (Ring){.items = items, .capacity = capacity, .head = 0, .size = 0};
    return 1;
}

void ring_destroy(Ring *r) {
    if (r == NULL) return;
    free(r->items);
    *r = (Ring){0};
}

int ring_push(Ring *r, int value) {
    if (r->size == r->capacity) return 0;
    size_t tail = (r->head + r->size) % r->capacity;
    r->items[tail] = value;
    ++r->size;
    return 1;
}

int ring_pop(Ring *r, int *out) {
    if (r->size == 0) return 0;
    *out = r->items[r->head];
    r->head = (r->head + 1) % r->capacity;
    --r->size;
    return 1;
}

int ring_front(const Ring *r, int *out) {
    if (r->size == 0) return 0;
    *out = r->items[r->head];
    return 1;
}
