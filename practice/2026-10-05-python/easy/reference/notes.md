# Notes — First Revisited Station

## Recognition signal
The prompt asks whether each item has been seen **before** while preserving encounter order. That strongly suggests a set.

## Brute force
For every position, scan the earlier prefix for the same station: O(n²) worst-case time, O(1) extra space.

## Optimal approach
Maintain a set of stations already seen. Test membership before insertion.

Expected time: O(n). Space: O(n).

## Invariant
Before processing index i, `seen` contains exactly the values at indices 0 through i-1.

## Common mistakes
- Returning the most frequent value rather than the earliest revisit.
- Adding before checking.
- Sorting and destroying arrival order.

## CS61B connection
Direct hash-table/set lookup: trade O(n) storage for an expected linear scan.
