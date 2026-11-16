# Easy reference notes — K-th Highest Incident Priority

## Recognition signals

The wording **k-th largest**, **streaming**, **retain only k**, and **no full sorting** points to the **heap / top-k** CS61B pattern. A sorting solution is legitimate as a baseline, but it works harder than necessary when k is small.

## Brute force versus optimal

**Baseline:** Sort the whole array descending and return element k−1. This takes O(n log n) time. Python's sorted creates O(n) output space (its sorting internals may need additional workspace). Repeatedly scanning for the maximum k times would cost O(nk).

**Optimal for the requested scan/space model:** Build a Python **min-heap** of the first k elements using heapq.heapify. The heap holds the k highest priorities among all the inputs processed so far, counting duplicates as individual entries. For a new priority p:

1. If p ≤ heap[0], it cannot displace any of the current k best entries. Ignore it.
2. If p > heap[0], replace the smallest retained priority with p using heapq.heapreplace.

At the end, heap[0] is the k-th highest value overall. A min-heap is intentional: its smallest retained value is the eviction candidate. Compare **heapreplace** with pop+push (one fused operation). Input order is irrelevant, but we never reorder the original list.

## Correctness invariant and proof

After examining i ≥ k priorities, the heap consists of a multiset of exactly the k largest values in that prefix. Base case: true after initializing on the first k items. Induction: a new value no greater than the smallest retained member cannot enter the prefix's top k; otherwise it replaces exactly that member. Ties do not affect the returned numerical priority, but duplicates remain separate heap entries. The root is the least member of this top-k multiset, so it has rank k in descending order.

## Complexity

Heap creation O(k); each of n−k arrivals costs O(1) if ignored and O(log k) if replaced. Total **O(k+(n−k)log k)**, customarily **O(n log k)**, with **O(k)** extra memory. When k=n, building the heap is linear. Heap internals guarantee logarithmic operations, not O(1) insertions.

## Common mistakes

- Use a max-heap and accidentally keep the k *smallest* values.
- Call heapq.nlargest and inadvertently store all k results when trying to explain a hand-built heap.
- Drop duplicates using a set, changing the definition of rank.
- Return heap[-1], which has no meaningful extremal guarantee.
- Forget k=1, k=n, all negative values, or empty/invalid input.
- Confuse heap **array representation** with a sorted list: only parent ≤ children is enforced.

## CS61B links

Binary heaps are priority queues with structural and heap-order invariants; pushing or replacing triggers swim/sink. The same top-k idea powers bounded-memory dashboards, streaming selection, and efficient retrieval of candidates. Contrast a balanced BST with O(log n) ordered operations but greater bookkeeping, and quickselect with expected O(n) when the whole batch is available.
