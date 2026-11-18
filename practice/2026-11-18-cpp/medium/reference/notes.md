# Optimal explanation — Minimum Calibration Group Span

## Recognition signals

The objective says **minimize the maximum** span, while input is **sorted**, and a threshold X makes a yes/no feasibility question straightforward. This is the classic signal for **binary search on the answer**, but the feasibility check and its proof must be derived from this grouping problem.

## Brute force versus optimal

**Brute force:** among n-1 gaps, choose cuts to form up to k contiguous groups. Enumerating all cut masks costs O(n·2^(n-1)) time with a straightforward scan per mask, O(n) recursion/cut-list space or O(1) extra with an integer mask when n is tiny. A dynamic programming alternative can take O(k n²) time.

**Optimal:** for a candidate span X, greedily start a group at the earliest unassigned timestamp, include every subsequent timestamp within X of that start, and open a new group at the first timestamp that would exceed X. Count groups; feasible iff count <= k.

If X works, every larger threshold works. Binary-search the first feasible X in [0, maxTime-minTime]. Each check scans n timestamps, so O(n log(R+1)) time where R=maxTime-minTime (at most 2^32-1). Additional space O(1).

### Copyable C++17 syntax

~~~cpp
long long lo = 0;
long long hi = (long long)a.back() - (long long)a.front();
while (lo < hi) {
    long long mid = lo + (hi - lo) / 2;
    if (canSplit(mid)) hi = mid;
    else lo = mid + 1;
}
return lo;
~~~

## Greedy invariant and correctness

Fix X. A group beginning at the earliest unassigned index i can legally extend at most through the last index j for which a[j]-a[i] <= X. Any legal partition's first group ends at j or **earlier**. Ending earlier cannot reduce the number of groups needed to cover the remaining suffix (you are leaving more sorted elements), so there is an optimal minimum-group partition that makes the greedy first cut. Repeat the exchange argument on the suffix. Thus greedy yields the **minimum number of groups** for X, proving feasibility.

Monotonicity: an existing partition under X is also valid under any Y >= X. Binary search maintains that the unknown minimum feasible X remains within [low, high] and terminates at its only candidate.

## Traps

1. Sorting an already sorted input needlessly or changing original order.
2. Checking just consecutive gaps: group span is last-minus-first, not a bound on each neighboring gap.
3. Off-by-one: a span equal to X is allowed; split only on > X.
4. Premature int subtraction: INT_MAX - INT_MIN overflows int. Cast operands to long long **before** subtracting.
5. Believing the scan is O(k n): groupStart changes, but each timestamp is visited once per check.
6. Requiring exactly k groups when at most k suffices (although any group can be split further if exactly k were requested).
7. Returning the last *infeasible* X instead of the first feasible X.

## CS61B transfer

This strengthens binary-search invariants and cost models, a direct curriculum goal. The greedy one-pass grouping resembles window pointer reasoning but differs because groups are finalized instead of shrinking a live window. A closely related interview pattern is partitioning workloads into k batches to minimize the heaviest batch (when batch weight is sum rather than span, the feasibility scan changes). Reattempt a one-page derivation of feasible(X), its monotonicity proof, and both binary-search boundary updates from memory.
