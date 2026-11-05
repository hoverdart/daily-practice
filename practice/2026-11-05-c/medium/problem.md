# Medium — Count Calm Signal Intervals

Given n integer sensor readings and a nonnegative tolerance L, a nonempty contiguous interval is **calm** if:

~~~text
maximum reading in interval - minimum reading in interval <= L
~~~

Return the **number** of calm contiguous intervals. Two intervals with the same values but different start/end positions count separately.

Implement:

~~~c
long long count_calm_intervals(const int *readings, int n, int tolerance);
~~~

### Examples

- readings = [4, 1, 3], tolerance = 2 -> 4: the three length-1 intervals and [1,3].
- readings = [2, 2, 2], tolerance = 0 -> 6.
- readings = [INT_MIN, INT_MAX], tolerance = INT_MAX -> 2: only the singletons fit.

### Constraints

- 0 <= n <= 200,000. A NULL pointer is allowed only when n = 0.
- 0 <= tolerance <= INT_MAX.
- Readings may be **any signed 32-bit integer**.
- The answer may exceed a signed 32-bit integer. Return a 64-bit long long.
- Target O(n) time and O(n) auxiliary space, using plain C (no built-in deque).

### Interview questions

1. How can two monotonic deques maintain the window maximum and minimum?
2. When the current window is calm, why do all its suffixes ending at the current right boundary also qualify?
3. If the smallest valid left boundary for right is left, how many new valid intervals end at right?
4. Why is comparing max-min using int potentially undefined behavior?

