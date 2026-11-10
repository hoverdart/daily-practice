# Reference notes — Two-Stack Alert Inbox

## Recognition signals

A FIFO interface built from strictly LIFO primitives is a **representation / amortized-analysis** exercise. Think CS61B stacks, queues, ADTs, and geometric-resizing-style accounting, not graph BFS (even though BFS consumes a queue).

## Baseline vs optimal

- Baseline: keep all tickets in an array and remove index 0 by shifting O(n) remaining entries. With q operations this costs O(q²) time in the worst case.
- Another baseline: for each dequeue, move everything between stacks and then restore it. Also potentially O(q²).
- Optimal: incoming stores newly enqueued tickets with newest on top; outgoing stores oldest tickets with oldest on top. Only when outgoing becomes empty do we pop every incoming ticket into outgoing, reversing their order.

Each ticket is pushed once into incoming, popped once from incoming, pushed once into outgoing, and popped once from outgoing (or peeked without removing). At most O(1) *total* stack transitions per ticket. So even if one operation costs O(q), **all** q operations together cost O(q), amortized O(1) per operation, O(q) auxiliary space.

## Invariant and correctness

All unconsumed tickets in outgoing are older than any ticket in incoming. Inside outgoing, the oldest remains on top; inside incoming, the newest remains on top. If outgoing is nonempty, its top must be returned first. Otherwise the reversal of incoming puts the globally oldest pending ticket on outgoing's top.

## Java syntax

~~~java
Deque<Integer> in = new ArrayDeque<>();
in.push(42);
int x = in.pop();   // never call if empty
Integer next = in.peek(); // null if empty
~~~

## Common mistakes

- Using addLast/removeFirst directly as a queue despite the two-stack restriction.
- Reversing incoming even when outgoing is nonempty, causing newer alerts to jump ahead of older ones.
- Treating peek as a destructive pop.
- Using zero or a legitimate positive ticket as the empty sentinel (only -1 means empty here).
- Claiming each operation is **worst-case** O(1) rather than **amortized** O(1).

## CS61B connections

Abstract data types vs their representations, deque and stack interfaces, loop invariants, O(1) primitive operations, and aggregate amortized complexity. This is a useful mental model for other infrequent-but-expensive operations such as resizing an ArrayList.
