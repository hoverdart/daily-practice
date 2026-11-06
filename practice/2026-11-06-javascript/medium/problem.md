# Medium — Exactly K Signal Collision Pairs

A receiver records a chronological array of integer event IDs. Within a contiguous interval, **one collision pair** is any choice of two distinct positions having the same event ID. The positions do not have to be adjacent.

For example, [4, 7, 4, 4] has three collision pairs: all three unordered pairs among the three occurrences of 4.

Implement:

~~~js
function countWindowsWithExactCollisions(ids, k) { /* number of nonempty intervals */ }
~~~

Return the number of **nonempty contiguous subarrays** containing exactly k collision pairs. Distinct intervals count separately, even if they have equal contents. Do not mutate ids.

### Example

ids = [2, 2, 3, 2], k = 1

Output: 3.

The qualifying intervals are [2,2] (positions 0–1), [2,2,3] (0–2), and [2,3,2] (1–3). The full interval contains three pairs, not one.

Other examples:
- ids = [5,5,5], k = 3 => 1.
- ids = [1,2,3], k = 0 => 6.
- ids = [], k = 0 => 0.

### Constraints

- 0 <= ids.length <= 120,000
- Each ID fits a signed 32-bit integer.
- 0 <= k <= 10,000,000,000.
- Number of intervals and collision pairs both fit safely inside a JavaScript Number for the given n.
- Target expected O(n) time and O(u) auxiliary space, where u is the number of distinct IDs.

### Think first

If the current window contains f copies of an ID x, adding another x forms how many new equal-ID pairs? What happens when its leftmost occurrence is removed? Counting **at most k** collisions may be easier than counting exactly k directly.
