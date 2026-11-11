# Easy — Archive Range Count Queries

A telemetry archive stores event IDs in a **sorted, nondecreasing** array. IDs can be negative, and duplicates are meaningful: each occurrence is a separate event.

An analyst submits inclusive ID ranges. For each range [low, high], return how many archived events have IDs between those endpoints, inclusive. The analyst may supply a range with low > high; its answer is zero.

Implement this exact C++17 interface:

~~~cpp
struct IdRange {
    int low;
    int high;
};
std::vector<int> archiveRangeCounts(
    const std::vector<int>& sortedIds,
    const std::vector<IdRange>& queries);
~~~

### Example

- IDs: [-3, -3, 0, 2, 2, 2, 9]
- Queries: [-3, -3], [1, 8], [-3, 2], [4, 3]
- Output: [2, 3, 6, 0]

The second range contains the three events with ID 2; the last range is reversed.

### Constraints

- 0 <= sortedIds.size(), queries.size() <= 200,000
- IDs and range endpoints are signed 32-bit integers.
- sortedIds is already sorted; do not sort, mutate, or copy it.
- Target O(log n) work per query, after O(1) setup; allow a constant-time empty-archive case.
- Return counts in original query order.

### Before coding

Scanning all events for every query is correct but slow when both arrays are large. Which two boundary positions uniquely determine a range's count? Pay special attention to inclusive high endpoints and duplicate IDs.
