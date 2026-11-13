# Medium — Longest Exact Net-Change Run

## Scenario

A system reports a signed change in stored capacity after each event: `deltas[i]` may be positive, zero, or negative. Find the **longest nonempty contiguous** run whose total net change equals `target`. Return `[start,end]` as a **half-open** interval (inclusive start, exclusive end). For equal longest lengths, return the one with **smallest start index**. If none exists, return `[-1,-1]`.

## Signature

```js
function longestExactNetRun(deltas, target) { /* [start,end] */ }
```

**Limits:** `0 <= deltas.length <= 140000`, `-1000000 <= deltas[i] <= 1000000`, `-140000000000 <= target <= 140000000000`. Sums fit exactly in JavaScript Number. Do not mutate input.

## Examples

```js
longestExactNetRun([2,1,5,2,1], 3)         // [0,2], ties [3,5]
longestExactNetRun([1,-1,3,1,-1], 3)       // [0,5]
longestExactNetRun([2,-3,1,4,-4], 0)       // [0,5]
longestExactNetRun([1,1,1], 5)            // [-1,-1]
```

Derive a quadratic brute-force scan. Why does the **standard sliding-window sum** approach break with negative numbers? Use the prefix equation `prefix[end]-prefix[start] = target`; decide which prefix occurrence to preserve to maximize length. Aim for expected **O(n)** time.
