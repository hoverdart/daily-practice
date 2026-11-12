# Medium — Recognition, correctness, complexity, pitfalls

## Recognition signals

A **contiguous** interval, a **maximum length**, and a nonnegative additive budget whose cost can only increase when extending right. This strongly suggests a variable sliding window. Unusually, the quantity being summed belongs to the *edges between elements*, not to the elements themselves.

## From brute force to optimal

A brute-force solution tries every start l, extends every end r, and updates the adjacent-change sum incrementally; this takes O(n^2) time and O(1) extra space. A more naive implementation recomputes each sum and takes O(n^3).

**Optimal O(n):** keep left, right, and a running drift for exactly the edges (left,left+1),...,(right-1,right). On extending to right, add the new edge from right-1 to right (unless right=0). While over budget, drop the single edge between left and left+1 and increment left. Check the current span's length after restoring feasibility.

## Invariant / proof

After the shrinking loop, drift is the sum of all internal adjacent changes in [left,right], and drift <= budget. Every nonnegative edge cost makes a longer leftward extension no cheaper. Therefore left is the **earliest feasible start** for the current right, and thus maximizes length for that right. Since each invalid earlier start can never become valid at a later right (only nonnegative edges get added), left never needs to move backward. Examining all right endpoints captures the global optimum. For equal lengths, prefer smaller left.

Each endpoint moves at most n times -> **O(n) time, O(1) extra space**. The total drift is bounded above by (n-1)*(2^32-1) for the given n and thus fits signed 64-bit.

## Common mistakes

- Subtract the removed **reading** rather than the edge (left,left+1).
- When moving right, add |a[right]| instead of |a[right]-a[right-1]|.
- Use abs(a-b) where a and b are int; subtraction may overflow **before** abs.
- Record the candidate before making the window valid.
- Return the last tie rather than the earliest start.
- Forget that a singleton has cost zero; an over-budget window can always shrink to one element.

## CS61B connections

This is amortized two-pointer analysis (each pointer advances O(n) times), closely related to sliding-window frequency invariants and weighted path costs. Treat a line of readings as a **path graph**; each adjacent pair is an edge with nonnegative weight. The window's drift is the total path weight between its endpoints.

