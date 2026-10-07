# Hard / Stretch — Stable Signal Under Noise

Given integer array `signal`, integer `k`, and nonnegative `limit`, return the longest contiguous window satisfying both: at most k distinct values, and `max(window)-min(window) <= limit`.

## Signature
```cpp
int longestStableSignal(const std::vector<int>& signal, int k, int limit);
```

Examples: `[1,3,2,2,5], k=3, limit=2 -> 4`; `[8,2,4,7], k=4, limit=4 -> 2`; `[4,4,4], k=1, limit=0 -> 3`; `[] -> 0`.

Target expected O(n). Try to avoid an ordered multiset.
