# Reference Notes — Solo Alerts in a Sorted Chain

## Recognition signals

- **Sorted singly linked list** → identical keys form uninterrupted runs; no hash table is necessary.
- **Remove an entire run** → inspect its end *before* changing links.
- **Possible deletion of head** → a stack-local sentinel plus a `tail` pointer removes head-special-case branching.
- **Must free removed nodes** → save `next` before `free`; never dereference freed storage.

## From brute force to optimal

One simple baseline copies the list into an array, scans each run, constructs an entirely new list, and frees the old list: O(n) time but O(n) extra memory and violates the reuse requirement. An especially naive approach rescans the whole list to count each key, O(n²). The optimal algorithm scans each run exactly once, splices only singleton original nodes into the output, and frees all nodes in repeated runs. Both scans combined traverse each input node a constant number of times.

## Precise invariant and proof

At each outer-loop start, `cur` points to the first not-yet-classified run. `dummy.next` through `tail` contains exactly the singleton nodes from fully processed runs, in original order. `end` is the first node with a different ID, or NULL. If `cur->next == end`, the run has length one and is appended. Otherwise, each node in [cur,end) is freed. This extends the invariant while never retaining a removed node as a linked successor of `tail` in the final result. Terminating with `tail->next = NULL` is essential when the final run was removed: it eliminates a potentially dangling link. Returning `dummy.next` is safe; returning `&dummy` would not be.

## Complexity

O(n) time; O(1) auxiliary space. Every discarded node is freed once; each retained node is reused, not copied.

## Common mistakes

1. Keeping one element from a repeated run rather than deleting the entire run.
2. Writing `cur = cur->next` *after* freeing cur (use-after-free).
3. Advancing `tail` into a run that will be freed.
4. Forgetting to terminate the output with NULL after deleting a repeated suffix.
5. Incorrectly returning the address of a stack-local sentinel.
6. Assuming `free(NULL)` is harmful (it is allowed), or freeing surviving nodes before the caller can use them.

## CS61B connections

Sentinel nodes, singly linked-list invariants, aliasing, O(1) relinking, and amortized-free traversal. Contrast with array deletion (requires shifting) and with a hash-set deduplication approach (extra memory, also a different specification).

## Minimal mental pseudocode

```text
dummy.next = head; tail = dummy
while cur exists:
    end = first node beyond cur's equal-ID run
    if end == cur.next: link cur after tail; tail = cur
    else: free each node from cur up to (excluding) end
    cur = end
tail.next = NULL
return dummy.next
```
