#include <assert.h>
#include <stdio.h>
#include "solution.c"

static unsigned rng = 987654321u;
static unsigned next_rand(void) {
    rng ^= rng << 13; rng ^= rng >> 17; rng ^= rng << 5;
    return rng;
}

int main(void) {
    Ring r = {0};
    int x = -999;
    assert(!ring_init(&r, 0));
    assert(ring_init(&r, 3));
    assert(!ring_pop(&r, &x) && x == -999);
    assert(!ring_front(&r, &x));
    assert(ring_push(&r, 10));
    assert(ring_push(&r, 20));
    assert(ring_push(&r, 30));
    assert(!ring_push(&r, 40));
    assert(ring_front(&r, &x) && x == 10);
    assert(ring_pop(&r, &x) && x == 10);
    assert(ring_push(&r, 40));
    assert(ring_pop(&r, &x) && x == 20);
    assert(ring_pop(&r, &x) && x == 30);
    assert(ring_pop(&r, &x) && x == 40);
    assert(!ring_pop(&r, &x));
    ring_destroy(&r);
    assert(r.items == NULL && r.capacity == 0 && r.size == 0);

    assert(ring_init(&r, 1));
    assert(ring_push(&r, -7));
    assert(!ring_push(&r, 9));
    assert(ring_pop(&r, &x) && x == -7);
    assert(ring_push(&r, 9));
    assert(ring_front(&r, &x) && x == 9);
    ring_destroy(&r);

    assert(ring_init(&r, 17));
    int model[17] = {0};
    int head = 0, size = 0;
    for (int t = 0; t < 10000; ++t) {
        if ((next_rand() % 3) != 0) {
            int value = (int)(next_rand() % 2001) - 1000;
            int ok = ring_push(&r, value);
            assert(ok == (size < 17));
            if (ok) { model[(head + size) % 17] = value; ++size; }
        } else {
            int ok = ring_pop(&r, &x);
            assert(ok == (size > 0));
            if (ok) {
                assert(x == model[head]);
                head = (head + 1) % 17;
                --size;
            }
        }
        assert(r.size == (size_t)size);
        int ok = ring_front(&r, &x);
        assert(ok == (size > 0));
        if (ok) assert(x == model[head]);
    }
    ring_destroy(&r);
    puts("easy: ring buffer tests passed");
    return 0;
}
