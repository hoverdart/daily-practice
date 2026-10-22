# Medium — Longest Stable Telemetry Window

A device reports a chronological array of signed integer readings. A contiguous interval is **stable** when its maximum reading minus its minimum reading is at most limit. Find the **longest** stable interval. Break ties by choosing the **earliest start index**.

Implement in C:

    typedef struct { int start; int length; } Segment;
    Segment longest_stable_segment(const int *readings, int n, int limit);

Return {0,0} for an empty array. For nonempty input, return the zero-based start index and positive length. Do not mutate the input.

**Examples:**
- readings=[8,2,4,7], limit=4 → {1,2} (window [2,4]).
- [5,5,5], limit=0 → {0,3}.
- [4,1,4,1], limit=2 → {0,1}.
- [-2147483648,2147483647], limit=0 → {0,1}.

**Constraints:** 0 ≤ n ≤ 200,000; 0 ≤ limit ≤ 2,147,483,647; readings are any signed 32-bit integers. Target **O(n)** time, **O(n)** extra space. Brute-force range scans are too slow. In C, compute max−min in **64-bit arithmetic** to avoid overflow.

**Think:** As the right endpoint advances, maintain the current window's maximum and minimum in **two index deques**. Why can each index be pushed and popped at most once from each deque?
