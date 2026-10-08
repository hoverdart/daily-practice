# Easy — Bounded Dispatch Ring

A small device processes integer job IDs in FIFO order. Its fixed-capacity buffer must reuse freed slots rather than shifting the entire array.

Implement a **circular queue** in C. The provided `Ring` struct holds a heap-allocated integer array, its `capacity`, the index `head` of the oldest item, and the number of live elements `size`.

## Required API

    typedef struct {
        int *items;
        size_t capacity, head, size;
    } Ring;

    int ring_init(Ring *r, size_t capacity);
    void ring_destroy(Ring *r);
    int ring_push(Ring *r, int value);
    int ring_pop(Ring *r, int *out);
    int ring_front(const Ring *r, int *out);

- `ring_init`: return 1 on successful allocation; return 0 for zero capacity or allocation failure. On success initialize every field.
- `ring_destroy`: free owned storage and reset all fields to zero/NULL. Called only on zero-initialized or successfully initialized rings.
- `ring_push`: append to the back and return 1, or return 0 without changing the ring if full.
- `ring_pop`: remove oldest item into `*out` and return 1; return 0 and **leave `*out` unchanged** if empty.
- `ring_front`: peek without removing, with the same empty behavior.
- Calls to push/pop/front occur only after successful initialization; `out` is non-NULL.

## Example

Capacity 3: push(10), push(20), push(30) => full. Pop returns 10. Push(40) reuses the slot freed by 10. The next pops return 20, 30, 40.

## Constraints and target

`1 <= capacity <= 10000` for successful initialization; up to 100000 operations; job IDs may be negative. Aim for **O(1) worst-case** push/pop/front, **O(capacity)** owned memory, and no shifts. Consider capacity 1, wraparound, empty/full transitions, and `malloc`/`free` ownership.

**CS61B connection:** array-backed queues, circular deques, representation invariants, and the tradeoff between indexing and linked nodes.
