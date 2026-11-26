# Repeated-ID Window Census (Medium)

A stream records device IDs. A nonempty contiguous window is admissible if at most k distinct IDs occur **at least twice** inside it. Count all admissible windows, counting different index intervals separately. An ID occurring five times counts as one repeated ID, not four or ten.

Implement `long long repeated_windows(const int *ids, int n, int universe, int k)`. `0<=n<=200000`, `1<=universe<=200000`, `0<=k<=universe`, each ID is in `[0,universe)`. NULL is allowed for n=0. Inputs are read-only; free all scratch allocations before returning. Assume allocation succeeds (abort on failure is acceptable). Aim for O(n+universe) time.

Example: `[0,0,1,1]`, universe=2, k=1 gives 9: only the full window violates the rule. For `[0,0,0]`, k=0 gives 3 (singletons); k=1 gives 6. Empty stream gives 0. The answer can exceed INT_MAX.
