# Easy — First Nearby Duplicate Signal

A sensor gateway receives integer event IDs in arrival order. Return the **earliest index j** (0-based) for which an earlier equal ID exists at some index i with `0 <= i < j` and `j - i <= k`. Return `-1` if no such index exists.

Implement:

```js
function firstNearbyDuplicate(ids, k) // number
```

**Examples**

- `ids = [8, 3, 5, 8, 3], k = 3` → `3` (indices 0 and 3).
- `ids = [4, 7, 4], k = 1` → `-1`.
- `ids = [2, 2], k = 0` → `-1` (the two indices must differ).
- `ids = [5, 1, 5, 1], k = 2` → `2`.

**Constraints:** `0 <= ids.length <= 200_000`; IDs are safe integers (possibly negative); `0 <= k <= 200_000`. Do not modify the input.

**Target:** O(n) time and O(min(n, k)) extra space (or better). Explain exactly which earlier indices are present in your sliding data structure *before* you test index j.
