# Medium — Longest Trace With Limited Repeated Handoffs

A monitoring system records the station visited by a roaming diagnostic robot after each hop. The history is an array of station IDs. Each pair of consecutive visits forms a **handoff**.

For auditing, a handoff between A and B is considered **the same type** as a handoff between B and A. Visits A -> A are valid self-handoffs. If a handoff type occurs f times in a contiguous trace, its repeat count is max(0, f - 1); its first occurrence is free. The trace's **repeat count** is the sum across all handoff types.

Find the longest nonempty contiguous subarray of station visits whose repeat count is at most k.

Return a pair {startIndex, length}. Among equally long traces, choose the smallest start index. If the visit history is empty, return {0, 0}.

Implement:

~~~cpp
std::pair<int, int> longestHandoffTrace(
    const std::vector<int>& stations, int maxRepeats);
~~~

### Example

- stations: [5, 7, 5, 9, 7, 9]
- maxRepeats: 1
- Output: {0, 5}

The first five visits create handoffs (5,7), (7,5), (5,9), and (9,7): only the (5,7) type repeats. The whole six-visit trace adds a second repeated type (7,9).

### Constraints

- 0 <= stations.size() <= 200,000
- Station IDs are signed 32-bit integers, including negative values.
- 0 <= maxRepeats <= 200,000
- Target expected O(n) runtime and O(n) worst-case auxiliary space.
- Preserve the input; use C++17 STL.

### Before coding

Every subarray of visits contains one fewer handoff than visits. When a window grows on the right, what **single new handoff** appears? When the left endpoint moves forward, which **single old handoff** disappears? Think carefully about the distinction between the first and later copies of a type.
