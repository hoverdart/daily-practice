# Easy — Merge Two Calibrated Chains

Two monitoring devices report **nondecreasing** integer readings in singly linked lists `a` and `b`. Merge them into one nondecreasing list **by relinking the original nodes**. Do not allocate, delete, or copy any data nodes. When readings are equal, take the node from list `a` first (stable cross-list tie rule). Return the new head.

The supplied `Node` has `int value` and `Node* next`. Implement:

```cpp
Node* mergeCalibratedChains(Node* a, Node* b);
```

Example: a = 1 → 3 → 3 → 8, b = 2 → 3 → 7 gives 1 → 2 → 3(a) → 3(a) → 3(b) → 7 → 8. Either input may be null; both null returns null. Negative readings and duplicates are allowed.

**Constraints:** 0 ≤ total nodes ≤ 200,000; inputs are acyclic, disjoint, and individually sorted. **Target:** O(n+m) time, O(1) extra space (not counting the original nodes). Avoid recursive depth proportional to list length. Explain why `<=` matters for stability and what ownership assumptions permit in-place rewiring.
