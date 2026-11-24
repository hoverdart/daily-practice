# Medium — Longest Quiet Block

A build farm records a sequence of job IDs. Repeated IDs inside one contiguous block can interfere: every unordered pair of **different positions** carrying the same ID contributes one conflict. A block with three copies of ID 7 therefore contributes three conflicts, not two.

Given a nonnegative conflict budget, return the maximum length of a contiguous block whose total conflict count is at most the budget.

```java
public static int longestQuietBlock(int[] ids, long budget)
```

Return 0 for an empty array. Do not mutate ids.

## Examples
- ids = [1,2,1,2,1], budget = 2 -> 4. The first four positions contain two pairs; all five contain four.
- ids = [4,4,4,4], budget = 3 -> 3. Three identical IDs create 3 pairs; four create 6.
- ids = [-1,2,-1,3,2,4], budget = 0 -> 4 ([-1,3,2,4]).
- ids = [], budget = 9 -> 0.

## Constraints
- 0 <= ids.length <= 200,000.
- IDs may be any signed Java int.
- 0 <= budget <= Long.MAX_VALUE.
- Inputs are non-null.
- Aim for expected O(n) time. Pair counts can exceed Integer.MAX_VALUE.
