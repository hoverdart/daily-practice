# Reference Notes — Cumulative Calibration Patches

## Recognition signals
A batch of many **additive interval updates**, followed by one request for **all** final values, suggests a **difference array + prefix sum**. There are no interspersed point queries. If online updates/queries were required, a Fenwick tree or segment tree might be appropriate instead.

## Brute force versus optimal
The direct method touches every position of every patch, `O(nq)` in the worst case. Instead, record the **change in accumulated value** at interval boundaries: `diff[left] += delta`, `diff[right+1] -= delta`. Prefix-summing these signed events reconstructs the final array in one pass.

## Invariant and proof
After processing all patches, `diff[i]` represents the net effect starting at index `i` minus effects ending just before `i`. During the scan, `running = sum(diff[0..i])` is exactly the sum of all patch deltas whose inclusive ranges contain `i`. Each patch contributes +delta beginning at `left` and -delta beginning at `right+1`.

## Complexity
`q` updates each touch two cells, so `O(q)`, followed by `O(n)` reconstruction: **O(n+q) time, O(n) space**. Each output slot must be written anyway.

## Common mistakes
- Forgetting inclusive semantics and subtracting at `right` rather than `right+1`.
- Allocating only `n` boundary cells, then writing past the end for `right=n-1`.
- Summing deltas in `int` and overflowing even when each patch fits an `int`. Use `long[]` and `long running`.
- Repeatedly walking the full interval, losing the linear-time improvement.
- Misinterpreting `diff[i]` as the absolute reading rather than a *change*.

## CS61B connections
Arrays, sequential traversal, prefix sums, and runtime cost models. This is the dual of range-sum queries: prefix sums answer many static queries; a difference array handles many batch range updates.

## Follow-up
If asked to support online `rangeAdd` and `pointQuery`, how could a Fenwick tree store the difference events?