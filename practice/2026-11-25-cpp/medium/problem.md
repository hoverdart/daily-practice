# Longest Calibration Span With One Free Reading — Medium

A calibration recorder stores nonnegative processing costs in chronological order. A technician may waive the entire cost of **at most one reading** inside a chosen contiguous span. Find the maximum number of readings in a span whose remaining cost is at most a nonnegative budget.

Implement:

```cpp
int longestFreeSpan(const std::vector<int>& costs, long long budget);
```

Examples:
- costs=[4,9,2,3], budget=5 -> 3 (choose [9,2,3], waive 9; no length-4 span is affordable).
- costs=[8,1,1,8], budget=2 -> 3.
- costs=[0,0,0], budget=0 -> 3.
- costs=[], budget=7 -> 0.

Constraints: 0 <= n <= 200,000; 0 <= costs[i] <= 1,000,000,000; 0 <= budget <= 200,000,000,000,000. Return 0 for empty input. Do not reorder readings. Aim for O(n) time. Explain why discarding an invalid left endpoint is safe, and why a running maximum that never decreases is not generally safe for tracking exact window validity.
