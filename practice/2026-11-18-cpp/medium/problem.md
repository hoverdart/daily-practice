# Medium — Minimum Calibration Group Span

An instrument reports a **sorted** array of calibration timestamps (signed 32-bit integers). You must partition the array into **at most k nonempty groups**, preserving the original order. Each group must be contiguous in the array; no timestamp can be discarded.

The span of a group is its final timestamp minus its first timestamp. The cost of a partition is the **largest group span**. Return the smallest achievable cost.

Implement this C++17 function:

~~~cpp
long long minimumCalibrationSpan(
    const std::vector<int>& sortedTimes, int maxGroups);
~~~

### Example

- sortedTimes = [1, 2, 3, 10, 11, 12], maxGroups = 2
- Answer = 2

Choose groups [1, 2, 3] (span 2) and [10, 11, 12] (span 2). One group would have span 11.

### Constraints

- 1 <= sortedTimes.size() <= 200,000
- 1 <= maxGroups <= sortedTimes.size()
- Values are sorted nondecreasing signed 32-bit integers (duplicates permitted).
- Do not mutate the input or build a quadratic DP table.
- Target O(n log R) time and O(1) extra space, where R is the full timestamp range plus one.

### Think first

For a proposed maximum allowed span X, can you test in one scan whether some partition fits in at most k groups? If you can partition under X, can a larger limit ever become impossible? What makes the greedy choice of keeping each group open as long as possible safe?
