# Recognition, reasoning, and reference — Shortest distinct coverage

**Recognition signals:** contiguous subarray, at least `k` different values, and *minimum length*. A frequency table tracks exactly which IDs occur in the current interval. The byte-sized alphabet means a fixed `int count[256]` replaces a hash map.

**Baseline:** For every left endpoint, scan rightward, maintaining a fresh 256-entry seen table until `k` types appear. This is `O(n² + 256n)` worst-case time, `O(256)` memory. Recounting every candidate interval from scratch would be even worse.

**Optimal invariant:** At each expansion, `count[id]` is the number of occurrences of that ID in the inclusive window `[left,right]`, and `distinct` equals the number of positive table entries. On insertion, `count[id]++ == 0` detects a newly present type. While `distinct >= k`, the current window qualifies: record it, then remove its leftmost element to search for a shorter qualifying window with the same right endpoint. On removal, `--count[id] == 0` detects a type disappearing.

**Why shrink while valid?** For a shortest-window objective, every currently valid window is a candidate, and removing from the left is the only way to shorten it. For longest-valid-window problems, by contrast, you typically shrink *while invalid*. Update the answer only for strictly shorter lengths: traversing left-to-right then preserves the earliest start on ties.

**Complexity:** `O(n+256)` time including table initialization. `right` advances `n` times; `left` also advances at most `n` times, despite the nested loop. `O(256)` auxiliary space, independent of `n`.

**Common mistakes:** using `char` as an array index (may be signed), decrementing distinct on every removal rather than only at zero, shrinking only once, using `distinct > k` instead of `>=`, updating the answer after invalidating the window, treating `k=0` as a normal case, and missing impossible coverage. `k=0` returns `{0,0}`; no qualifying nonempty segment returns `{-1,0}`.

**CS61B connections:** The 256-entry table is direct addressing; a hash table would generalize it to arbitrary IDs. The `O(n)` bound is an amortized two-pointer proof: total pointer movements, not nesting depth, determine the runtime.
