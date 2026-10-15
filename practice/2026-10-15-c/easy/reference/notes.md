# Reference Notes — Compact Sorted Telemetry IDs

## Recognition signals and baseline
Sorted array + remove duplicates + in place + return new length suggests two pointers. Equal values form adjacent groups. A temporary output array gives O(n) time but O(n) memory; shifting duplicates one at a time can take O(n²).

## Optimal algorithm
If n is zero, return zero. Initialize write=1 and scan read from 1 to n-1. If a[read] differs from a[write-1], assign a[write]=a[read] and increment write. Return write.

## Correctness invariant
Before each iteration, a[0..write-1] contains exactly the distinct values among the already-scanned original input, in sorted order. The next distinct value extends that prefix. Since write never exceeds read, overwriting a[write] never destroys unread input.

## Complexity
One scan: O(n) time and O(1) extra space. C arrays do not carry length metadata; n is a separate parameter.

## Common mistakes
- Reading the first element for n=0.
- Comparing against the wrong retained value.
- Returning read instead of write.
- Expecting the array to resize rather than using its valid prefix.
- Allocating a hash set despite sorted input.

## CS61B connections
This is an array-list representation-invariant exercise. Follow-ups include keeping at most two copies of each value, filtering an unsorted array by predicate, and merging two sorted arrays into spare trailing capacity.
