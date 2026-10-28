# Medium — Count Overloaded Signal Windows

A telemetry stream contains integer device IDs. A contiguous window is **overloaded** if it contains at least `k` *collision pairs*. A collision pair is an unordered pair of distinct positions `(i,j)`, `i<j`, holding equal IDs.

Count **all nonempty contiguous windows** that are overloaded.

```cpp
long long countOverloadedWindows(const std::vector<int>& ids, long long k);
```

**Examples**

- `ids=[1,1,1], k=1` → `3` (both length-2 windows and the length-3 window)
- `ids=[1,1,1], k=2` → `1` (only the whole array)
- `ids=[2,2,3,2], k=2` → `1`
- `ids=[7,8,9], k=1` → `0`
- `ids=[7,8,9], k=0` → `6` (every nonempty window qualifies)

**Constraints:** `0 <= n <= 200000`; IDs are signed 32-bit integers; `0 <= k <= 20000000000`. The answer may exceed 32-bit range.

**Target:** expected O(n) time and O(d) auxiliary space, where d is the maximum number of distinct IDs in a maintained window. Use an incrementally updated pair count; do not enumerate windows. Explain why counting the complement of **at most k-1 pairs** is convenient and why k=0 needs special handling.

