# Easy — Longest Distinct Sensor Window

A machine emits integer sensor codes. Return the length of the longest contiguous window containing at most `k` distinct codes.

## Signature
```cpp
int longestDistinctWindow(const std::vector<int>& readings, int k);
```

Examples: `[1,2,1,2,3], k=2 -> 4`; `[4,4,4], k=1 -> 3`; `[], k=3 -> 0`; `[1,2], k=0 -> 0`.

Constraints: up to 200000 readings. Target expected O(n) time using a frequency map.
