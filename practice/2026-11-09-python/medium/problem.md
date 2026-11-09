# Medium — Smallest Complete Sensor Snapshot

A telemetry system records a chronological stream of integer sensor IDs. An auditor needs a **contiguous** snapshot that contains at least a requested number of occurrences of **each** specified ID. Extra occurrences and IDs not in the request are allowed.

Implement:

~~~python
def smallest_complete_snapshot(
    events: list[int], required: dict[int, int]
) -> tuple[int, int]:
    ...
~~~

Return the shortest valid snapshot as a half-open interval **(start, end)**, meaning events[start:end]. If several valid snapshots have the same minimum length, choose the **earliest start**. If no snapshot meets all requests, return (-1, -1). If required is empty, return (0, 0), even when events is empty.

### Example

~~~text
events   = [8, 5, 8, 7, 5, 8, 7]
required = {8: 2, 5: 1}
answer   = (0, 3)   # events[0:3] = [8, 5, 8]
~~~

A snapshot with one occurrence of 8 is not sufficient: required quantities matter, not just distinct IDs.

### Constraints

- 0 <= len(events) <= 200,000
- Event IDs are signed integers in [-10^9, 10^9].
- Every value in required is a **positive** integer; keys are valid signed IDs.
- The sum of requested quantities may exceed len(events), making the answer impossible.
- Do not mutate events or required.
- Target expected O(n + u) time and O(u) extra working space, where n is stream length and u is the number of requested distinct IDs. (The input itself is not counted.)

### Before coding

A brute-force solution enumerates every start/end pair and counts IDs. Can one moving right pointer and one moving left pointer maintain how much of the request remains unmet? What does a **negative** requirement balance represent when a sensor appears more often than needed?
