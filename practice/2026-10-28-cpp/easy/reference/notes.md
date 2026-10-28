# Reference notes — Kth Strongest Calibration Pulse

## Recognition signals
The words **kth-largest**, **streaming**, and **k much smaller than n** suggest a heap holding only the current top k, rather than sorting all observations. In C++, `priority_queue` is a max-heap by default; `greater<int>` changes it to a min-heap.

## Brute force vs. optimal
A naive approach repeatedly searches for the maximum k times: O(nk). Sorting all n readings gives O(n log n) time and, depending on sorting strategy, additional storage or mutation. A min-heap of at most k entries uses O(n log k) time and O(k) extra space without changing the input. A selection algorithm can achieve expected O(n) offline, but the heap is especially appropriate when readings arrive online and bounded storage matters.

## Invariant and proof
After each prefix of at least k readings, the heap contains the k largest **occurrences** from that prefix; its root is the smallest of those, hence the kth-largest overall. Before k entries arrive, push each value. Afterward, any new value at most the root cannot change the kth-largest value, so discard it. A larger value displaces the root and preserves the invariant. Equal values count separately: no set or deduplication is allowed. Ignoring an equal-to-root value is safe for the returned rank because replacing an equal root changes no value in the multiset of top-k amplitudes.

## Complexity
Each input causes at most one heap insertion and one removal, each O(log k). Total O(n log k), O(k) auxiliary space. The worst-case heap size is exactly k. The input is read-only.

## Common mistakes
- Use the default **max**-heap, whose root is the largest, not the kth-largest.
- Deduplicate equal amplitudes.
- Return the minimum of the entire array instead of the heap root when k is small.
- Pop before checking heap size, or use `>= k` where `< k` is needed.
- Forget `#include <functional>` for `std::greater<int>`.
- Mutate the input by sorting when the contract forbids it.

## CS61B connections
The priority queue uses a binary heap, with a shape invariant (complete tree) and order invariant (each parent <= its children for a min-heap). Insert swims and removal sinks in O(log k). The same pattern solves top-k scores, kth-largest streams, and bounded-memory ranking. Contrast with a BST (ordered search) and hash set (membership without rank).

