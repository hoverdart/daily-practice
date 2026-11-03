# Cumulative Calibration Patches (Easy)

A sensor initially reports zero in each of `n` consecutive slots, indexed 0 through `n-1`. An engineer submits patches `[left, right, delta]`. Each patch adds `delta` to **every** slot in the **inclusive** range `left..right`. Patches can overlap, have negative deltas, and occur in any order.

Implement:

~~~java
public static long[] applyPatches(int n, int[][] patches)
~~~

Return all final readings in index order. Do not mutate the input patches. When `n=0`, the patches array is empty and the answer is empty.

**Example**

~~~text
n = 5
patches = [[0,2,4], [1,3,-2], [3,4,7]]
answer  = [4,2,2,5,7]
~~~

**Constraints:** `0 <= n <= 200_000`; `0 <= patches.length <= 200_000`; for each patch, `0 <= left <= right < n` and `-1_000_000_000 <= delta <= 1_000_000_000`. Use `long` for accumulated readings. Target `O(n + q)` time and `O(n)` extra space, where `q` is patch count.

**Interview checkpoints:** What happens at `right+1`? Why should the working array be one element longer than the output? Why can a reading overflow `int`? Why is a prefix scan enough?