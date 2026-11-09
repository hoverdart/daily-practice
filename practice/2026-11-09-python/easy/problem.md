# Easy — Merge Service Windows

A maintenance team reports **closed** time windows during which a service is unavailable. Each report is a pair [start, end], with start < end. Reports can be unsorted, repeated, nested, or overlapping. Windows that share an endpoint also count as connected: [2, 5] and [5, 8] represent one continuous outage.

Write:

~~~python
def merge_service_windows(windows: list[list[int]]) -> list[list[int]]:
    ...
~~~

Return the **minimal sorted list** of merged closed windows. No two returned windows may overlap or touch. **Do not modify** the input or any of its nested lists.

### Example

~~~text
windows = [[8, 10], [1, 4], [3, 6], [6, 9], [15, 17]]
result  = [[1, 10], [15, 17]]
~~~

The first four reports are connected transitively, including a touch at time 6. The final report remains separate.

### Constraints

- 0 <= number of windows <= 200,000
- -10^9 <= start < end <= 10^9
- Target O(n log n) time (from sorting) and O(n) additional space including the output.
- An empty input returns an empty list.

### Before coding

A brute-force method could build a graph where overlapping reports are connected and merge each connected component. Can sorting by start make the component boundaries apparent without building that graph? What does the last merged interval mean at each iteration?
