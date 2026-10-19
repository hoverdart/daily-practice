# Medium — Low-Load Processing Batches

A batch processor receives positive integer loads in order. A batch is a **nonempty contiguous segment**. It is safe when the **product** of its loads is strictly less than a threshold.

Return the number of safe batches, including overlapping batches.

~~~python
def count_light_batches(loads: list[int], limit: int) -> int:
    ...
~~~

### Examples

- loads = [10, 5, 2, 6], limit = 100 → **8**.
- loads = [1, 1, 1], limit = 2 → **6**.
- loads = [4, 4, 4], limit = 16 → **3** (only the singletons).
- loads = [1, 2, 3], limit = 1 → **0**.

### Constraints and rules

- 0 ≤ len(loads) ≤ 200,000.
- Every load is a positive integer (1 ≤ load ≤ 1,000,000); **zeros and negatives are excluded**.
- limit is an integer from -1,000,000 to 1,000,000,000.
- The inequality is strict: product == limit does **not** qualify.
- Do not modify the input. Return a potentially large integer.
- Target O(n) time and O(1) auxiliary space, under ordinary integer-arithmetic cost assumptions.

### Interview prompts

1. Why is a shrinking sliding window valid for **positive** numbers?
2. After repairing the window ending at right, how many valid segments end at right?
3. What special case avoids trying to shrink forever when limit ≤ 1?

