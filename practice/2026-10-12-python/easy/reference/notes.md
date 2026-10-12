# Reference Notes — First Unique Alert Stream

## Recognition signals
"First still-valid element in arrival order" + "new events invalidate old candidates" suggests a **queue/deque**, while "occurred exactly once" suggests **hash frequencies**. A set alone cannot distinguish one occurrence from three or preserve FIFO order.

## Brute force → optimal
For every prefix, rebuild a frequency table and rescan from the beginning to find its first unique ID. This takes O(n²) total time in the worst case and O(n) temporary space.

Instead, keep `counts[id]` for all seen IDs and a deque of IDs in their *first-arrival order*. Append an ID only when its count becomes 1. After every arrival, remove front candidates whose count is no longer 1. The front is then the earliest currently unique ID, or the deque is empty.

## Invariant and proof
After processing a prefix, every currently unique ID is still present in the deque in arrival order. Nonunique IDs may remain only **behind** the front; removing them is safe because counts never decrease, so they cannot become unique again. Thus the deque front, if any, is the first unique ID.

Each ID is appended **at most once** and removed **at most once**. Although the cleanup is a `while` loop nested in a `for` loop, its total removals are O(n), not O(n²). Expected O(n) time (hash operations) and O(n) auxiliary space.

## Common mistakes
- Append the same ID every time it appears; then the queue can contain multiple copies.
- Use a set and accidentally treat a third occurrence as unique.
- Inspect the deque front before removing invalidated entries.
- Use `list.pop(0)` (O(n)) instead of `deque.popleft()` (O(1)).
- Confuse `None` with an integer ID (negative IDs are legal).

## CS61B connection
This is a **queue invariant + hash-table counting** problem. CS61B's deque/circular-array amortized arguments explain why a stream of many `popleft` calls remains linear. Compare with the October 5 easy problem: both use hashing, but this one also requires ordering and multiplicity.
