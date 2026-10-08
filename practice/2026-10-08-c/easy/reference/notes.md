# Easy Reference Notes — Bounded Dispatch Ring

**Read after attempting the problem.**

## Recognition signals

Fixed capacity + FIFO + many operations + no shifting => circular array queue. Unlike a linked list, storage is contiguous and indices wrap using modulo.

## Brute force vs optimal

Brute: use a normal array and shift all elements left on pop. Pop costs O(capacity), even though enqueue is O(1). Better: keep a **head index** and a **size**; never move live elements.

## Representation invariant

For a nonempty ring, `items[head]` is the oldest item. Live elements occupy positions `(head+i)%capacity` for `i=0..size-1`. The next insertion goes to `(head+size)%capacity`. Always `0<=size<=capacity`; when `size==0`, head is an arbitrary valid index.

Pseudo:

    push(x):
      if size == capacity: fail
      items[(head+size) % capacity] = x
      size++
    pop():
      if size == 0: fail
      output items[head]
      head = (head+1) % capacity
      size--

After a pop, the physical slot is reusable. A push at full capacity must **not** overwrite an existing element. A failed pop/front must **not** touch the output pointer.

## Complexity

`ring_init` O(1) allocation call and O(capacity) allocated memory (allocator behavior aside). `ring_push`, `ring_pop`, `ring_front`: O(1) worst-case. `ring_destroy`: one `free` call, O(1) program-level operation. Total storage O(capacity).

## C-specific traps

- `malloc(capacity * sizeof(int))` allocates bytes, not element count; check for allocation failure and multiplication overflow.
- Initialize every struct field. `(Ring){0}` is a convenient zero-initializer.
- `ring_destroy` should call `free` exactly once on the owned pointer and reset fields. `free(NULL)` is legal.
- Do not compute `% capacity` if capacity can be zero; operations are only called on successfully initialized rings.
- `out` is a pointer to caller-owned storage: assign `*out`, not `out`.
- Watch unsigned `size_t` arithmetic and `head+size`; capacity is bounded in this exercise.

## CS61B connection

This is the array-backed queue/deque from CS61B: the invariant is more important than memorizing a particular implementation. A doubly linked list avoids modulo but allocates per node and loses cache locality.

## Next time, recognize

When repeated deletions from the front of an array would shift O(n) elements, think **circular buffer + head/size**.
