# Easy — Zero-Balance Telemetry Spans

A factory records a signed calibration change after each sample. A **balanced span** is a nonempty contiguous segment whose changes sum to **exactly zero**. Count all balanced spans, including overlapping spans.

Implement:

~~~python
def count_zero_sum_spans(values: list[int]) -> int:
    ...
~~~

### Examples

- values = [2, -2, 3, -3] → **3**: [2,-2], [3,-3], and the entire array.
- values = [0, 0, 0] → **6** (every nonempty contiguous segment).
- values = [1, 2, 3] → **0**.
- values = [] → **0**.

### Constraints and rules

- 0 ≤ len(values) ≤ 200,000; each element is an integer between -1,000,000 and 1,000,000.
- Do not modify the input.
- Return the number of segments (not their indices). It can exceed 32-bit integer range.
- Aim for expected O(n) time and O(n) auxiliary space.

### Interview prompts

1. How would you enumerate every possible segment in O(n²) time?
2. What does it mean if two **prefix sums** are equal?
3. Why must the frequency map initially contain the sum 0 exactly once?

