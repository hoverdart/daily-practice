# Medium — Longest Recalibratable Signal Run

A sensor logs a sequence of **signal codes**. During one contiguous monitoring interval, you may **recalibrate at most `k` readings** by changing each chosen code to any integer. The goal is to make **every code in that interval identical**.

Return the maximum possible interval length after at most `k` changes. You do **not** have to perform the changes or return the interval.

Implement:

```javascript
function longestRecalibratableRun(codes, k) {
  // Return maximum interval length.
}
```

**Input:** `codes` is an array of integers (each between -1e9 and 1e9), length `0 <= n <= 200000`; `k` is an integer with `0 <= k <= n`. Values may be negative, repeated, or widely separated. Do not mutate `codes`.

**Output:** one nonnegative integer.

**Examples:**

```
codes=[4,5,4,5,4,5], k=1  -> 3
codes=[1,2,2,1,2,2,2], k=1 -> 6
codes=[9,9,9], k=0        -> 3
codes=[], k=0             -> 0
codes=[1,2,3,4], k=4      -> 4
```

**Observation:** If a window has length `L` and its most common code appears `f` times, the minimum required changes are exactly `L - f`.

**Target:** expected `O(n)` time and `O(d)` auxiliary space for at most `d` distinct codes held in the frequency map. You may maintain a *historical*, nondecreasing maximum frequency; explain why it still gives the correct **maximum length**, even if it is not the current window's exact maximum after shrinking.

**Optional hint:** Expand right, update `freq[code]` and a running `maxFreq`, and shrink left while `windowLength - maxFreq > k`.
