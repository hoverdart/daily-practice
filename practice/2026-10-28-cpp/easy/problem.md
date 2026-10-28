# Easy — Kth Strongest Calibration Pulse

A lab records calibration pulses in arrival order. You need the **kth-largest pulse amplitude** seen in the entire stream. Equal amplitudes occupy separate ranks: for example, the second-largest element of `[8, 3, 8, 5]` is `8`, not `5`.

Implement:

```cpp
int kthLargestPulse(const std::vector<int>& pulses, int k);
```

**Examples**

- `pulses=[8,3,8,5], k=2` → `8`
- `pulses=[8,3,8,5], k=3` → `5`
- `pulses=[-7,-2,-7], k=3` → `-7`
- `pulses=[42], k=1` → `42`

**Constraints:** `1 <= pulses.size() <= 200000`; `1 <= k <= pulses.size()`; each amplitude is a signed 32-bit integer. The input must remain unchanged.

**Target:** `O(n log k)` time and `O(k)` extra space, even when `k` is much smaller than `n`. Explain what the heap's root means after each prefix and why duplicate values must be retained.

