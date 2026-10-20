# Reference — Next Higher Voltage Reading

## Recognition signals
“First later value **strictly greater** than this one” is a **next-greater-element** query. With a static array and an answer needed for every index, reach for a **monotonic stack**. This is a stack of **indices**, not readings: the indices are needed to calculate distances.

## Brute force → optimal
Brute force scans `j=i+1, i+2, ...` for each `i` until a larger reading appears: O(n²) time and O(n) answer space. Instead, scan once from left to right. Keep indices of readings still waiting for a larger successor. When reading `a[i]` is greater than the reading at the top index, it resolves that older index immediately; pop it and store `i-oldIndex`. Push `i` after resolving everything it can.

## Core invariant and proof sketch
The stack contains unresolved indices in increasing index order from bottom to top. Their readings are **non-increasing** bottom to top: a strictly greater new value would have popped smaller readings. When index `j` is popped by `i`, `a[i] > a[j]` and every index between `j` and `i` was processed without resolving `j`, so `i` is its **first** strictly greater successor. Equal values remain on the stack.

Each index is pushed exactly once and popped at most once, so the apparently nested loop performs at most 2n stack operations overall: **O(n) time, O(n) auxiliary space** (including result and stack). Stack height can reach n on a non-increasing array.

## Common mistakes
- Popping on `>=` instead of `>` answers “greater **or equal**,” which is wrong for plateaus.
- Pushing values instead of indices loses the wait distance.
- Looking for the global maximum to the right rather than the **first** greater reading.
- Calling `peek()` before checking `isEmpty()`.
- Claiming O(n²) merely because a while loop is nested inside a for loop; amortized counting is the key.

## Java syntax and CS61B connections
```java
Deque<Integer> stack = new ArrayDeque<>();
stack.push(i);
int topIndex = stack.peek();
int resolved = stack.pop();
```

This builds on CS61B stack/array-deque ADTs, loop invariants, and amortized runtime reasoning. Compare the same monotonic-stack idea in stock-span, histogram, and daily-temperature problems; change the inequality to match the exact prompt.
