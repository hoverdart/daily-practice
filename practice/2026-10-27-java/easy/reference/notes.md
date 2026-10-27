# Reference Notes — Closest Calibration Threshold

## Recognition signals

BST + closest value signals an **ordered search path**, not an exhaustive traversal. A BST node partitions all possible values into smaller and larger subtrees.

## Brute force versus optimal

A full traversal compares every node, O(n) time and O(h) recursive space. The optimal method follows only the usual BST search path and maintains the nearest visited value. When target is greater than the current value, all values in its left subtree are even smaller than current, so none can beat current. Symmetric reasoning holds for the right subtree when target is smaller.

## Invariant and complexity

After each visited node, best is the closest value among all visited nodes, preferring smaller values on ties. Every discarded subtree cannot improve on the current node, which was already considered. O(h) time and O(1) auxiliary space iteratively. Balanced BST: h=O(log n); skewed BST: h=O(n).

## Common mistakes

- int subtraction or Math.abs(int) can overflow for extreme values. Cast to long **before** subtraction.
- Forgetting to choose the smaller candidate on ties.
- Recursing into a 100,000-node chain, risking StackOverflowError.
- Exploring both subtrees and losing the ordered-search benefit.

## CS61B connections

BST search, ordered-data invariants, height/balancing, references, and the difference between O(log n) average balanced behavior and O(n) worst-case skew.
