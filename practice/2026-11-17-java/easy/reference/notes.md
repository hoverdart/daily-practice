# Reference notes — Oldest Unique Event in a Live Feed

## Recognition signals

A stream asks for the **oldest item whose status changes when later items arrive**. That calls for two complementary facts: a hash map answers "how many times has this ID occurred?", while FIFO order answers "which surviving unique ID appeared first?" A set cannot capture duplicate frequencies; sorting would destroy arrival order.

## Brute force to optimal

**Brute force:** after every arrival, count all prefix values and scan the prefix from the start for the first count equal to one. With a naive rescan, total work is O(n²) or worse, and extra space up to O(n).

**Optimal:** maintain a HashMap from ID to count and an ArrayDeque containing only IDs at their *first* occurrence, in arrival order. Increment the count. When it becomes one, append that ID. While the deque head's current count is not one, remove it. The head, if any, is the answer. We never need to remove stale IDs in the middle because an older stale ID cannot block a newer candidate once all stale heads are discarded.

## Core invariant and correctness

After cleanup, the queue head, if it exists, has count one and occurred earlier than every other currently unique ID. Each unique ID was enqueued on first appearance. An earlier duplicate might remain in the queue, but cleanup removes it before choosing the head. Because counts only increase, an ID that becomes nonunique can never regain uniqueness. Therefore removing it permanently is safe.

Each ID enters at most once and leaves at most once. The loop over queue heads has O(n) **successful removals in total**, not O(n) per event. Expected total time O(n) with average O(1) map operations; auxiliary O(n) for map, deque and result (excluding result, O(n)).

## Java syntax to memorize

~~~java
Map<Integer, Integer> count = new HashMap<>();
count.put(id, count.getOrDefault(id, 0) + 1);
ArrayDeque<Integer> q = new ArrayDeque<>();
q.addLast(id);
int first = q.peekFirst();   // call only when nonempty
q.removeFirst();
~~~

## Common mistakes

- Enqueuing every occurrence; duplicates may make later occurrences look unique.
- Using a set of currently unique IDs, which loses order.
- Assuming stale items must be removed from the middle immediately.
- Returning 0 for no answer even though ID zero is legal.
- Using an ArrayList and remove(0), making eviction O(n) each.
- Calling the nested cleanup loop O(n²) without aggregate analysis.

## CS61B connections

Hashing and collisions (expected, not unconditional worst-case, map operations), queues and ordering invariants, cost models and amortized analysis. Similar lazy-deletion techniques appear in heaps and event schedulers where full arbitrary deletions would be expensive.

