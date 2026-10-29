# Recognition, reasoning, and reference — Weighted scheduling with cooldown

**Recognition signals:** choose a compatible subset of time intervals, each with a reward, to maximize a sum. This is *weighted interval scheduling*, a dynamic-programming problem. The cooldown changes the compatibility test, not the DP structure. A shortest-path or MST algorithm is not appropriate.

**Brute force:** Enumerate all `2^n` subsets and check pairwise compatibility, retaining the maximum reward. Even a simple include/exclude recursion is exponential. Greedy earliest-finish works for maximizing the *number* of unweighted intervals, but fails with unequal rewards: one long lucrative job may beat several small ones, or vice versa.

**First improvement:** Sort jobs by end time. Let `dp[i]` be the best reward using the first `i` sorted jobs. For job `i` (zero-based), either skip it (`dp[i]`) or take it and combine its reward with the best compatible earlier prefix. A linear predecessor search gives `O(n²)` time.

**Optimal recurrence:** Compute `cutoff = (long long)job[i].start - cooldown`. Binary-search the first `j` among `[0,i)` whose `end[j] > cutoff`. Then exactly `j` earlier jobs have `end <= cutoff`, so

```text
dp[0] = 0
dp[i+1] = max(dp[i], reward[i] + dp[j])
```

The binary search uses a half-open interval `[lo,hi)` initialized to `[0,i)`. When `end[mid] <= cutoff`, advance `lo = mid+1`; otherwise `hi = mid`. At convergence, `lo` is the number of compatible preceding jobs. Because end times are sorted, all compatible earlier jobs form a prefix.

**Correctness invariant:** `dp[i]` is the optimum among the first `i` jobs. Any optimal subset either excludes job `i-1`, yielding at most `dp[i-1]`, or includes it, in which case every earlier selected job belongs to the compatible prefix. The recurrence considers both exhaustive cases.

**Complexity:** `qsort` costs `O(n log n)` expected/typical time (C does not mandate a worst-case complexity for `qsort`); `n` binary searches cost `O(n log n)`; DP costs `O(n)`. Total typical `O(n log n)` time and `O(n)` explicit extra space for the sorted copy and DP, plus implementation-dependent sort stack. The original input remains unchanged.

**Common mistakes:** greedy selection by reward; treating `[start,end)` as closed; forgetting cooldown on equality; searching through the current job; using `dp[j+1]` when `j` is already a *count*; integer overflow in `end + cooldown`, `start - cooldown`, or reward totals; writing a `qsort` comparator as `a->end - b->end`; not freeing both allocations if one fails. With zero rewards, skipping all jobs is legal.

**CS61B connections:** sorting and lower/upper-bound binary search turn a quadratic recurrence into a linearithmic algorithm. This extends the course's runtime analysis and ordered-search foundations into interview-style DP. The half-open prefix convention is the same one used in binary-search and array-backed collection invariants.
