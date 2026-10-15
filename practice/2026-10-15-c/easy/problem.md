# Easy — Compact Sorted Telemetry IDs

A machine exports a sorted array of integer telemetry IDs, but repeated readings cause duplicate IDs. Compact the array **in place**, preserving the sorted order, so its first k positions contain each distinct ID exactly once. Return k. Values after position k-1 are irrelevant.

Implement:

    int compact_sorted_ids(int *a, int n);

Example: [-9,-9,-2,0,0,0,7,9,9] becomes a prefix [-9,-2,0,7,9], and the function returns 5. An empty input returns 0. Negative IDs are allowed. 0 <= n <= 100000; the input is sorted nondecreasingly and writable. Do not allocate another array.

**Target:** O(n) time and O(1) auxiliary space. Think about what the compacted prefix means after processing each value. This connects to CS61B array lists, two-pointer invariants, and linear scans.
