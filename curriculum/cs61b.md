# CS61B Retention Curriculum

This curriculum is distilled from the supplied CS61B notes and organized for recurring interview practice rather than lecture order.

## Foundations

- Java typing, primitive vs. reference types, classes, instance/static members
- Arrays, ArrayLists, Maps, references
- Recursion and recursive linked structures
- Unit testing and test-driven development

## Lists and sequence structures

- Singly linked lists
- Doubly linked lists
- Sentinel nodes and invariants
- Array-backed lists
- Geometric resizing and usage ratios
- Circular arrays / deques
- Generics, interfaces, iteration

## Runtime reasoning

- Cost models
- Constant, logarithmic, linear, linearithmic, quadratic growth
- Recursive runtime reasoning
- Binary search
- Amortized intuition for resizing

## Connectivity and trees

- Disjoint sets
- Quick find / quick union
- Weighted quick union
- Path compression
- Binary search trees
- Balanced-tree motivation and B-trees

## Priority structures

- Priority queues
- Binary heaps
- Swim / sink
- Top-k / streaming selection
- Heap-backed sorting intuition

## Tree and graph traversal

- Preorder, inorder, postorder traversal
- Graph representations
- Depth-first search
- Breadth-first search
- Path reconstruction
- Cycle detection
- Connected components

## Graph algorithms

- Unweighted shortest paths with BFS
- Edge relaxation
- Dijkstra-style shortest paths
- Minimum spanning trees
- Union-find in Kruskal-style reasoning
- Directed acyclic graphs
- Topological sorting

## Hashing and strings

- Hash functions and hash codes
- Buckets / separate chaining
- Load factor and resizing
- `equals` / `hashCode` consistency
- HashMap / HashSet intuition
- Tries and prefix queries

## Sorting

- Selection sort
- Insertion sort
- Heap sort
- Merge sort
- Quicksort and partitioning
- Comparison-sort lower bounds
- Stable vs. unstable sorting
- Counting / radix-sort concepts

## Interview extensions

These are not necessarily central CS61B lecture topics, but the generator should gradually layer them on top of the foundations above:

- two pointers
- sliding window
- prefix sums
- monotonic stack / queue
- binary search on answer
- interval problems
- backtracking
- greedy methods
- dynamic programming
- bit manipulation

## Selection policy

A normal daily set should include:

1. **Easy** — implementation fluency or a recently weak fundamental.
2. **Medium** — a recognizable interview pattern connected to known material.
3. **Hard / stretch** — synthesis of two concepts, a new extension, or a more subtle invariant.

Do not make every hard problem an extreme competitive-programming problem. Difficulty is relative to the learner's current familiarity.

Prefer spaced repetition over random coverage. If an `attempt.md` shows a miss, hint dependency, incorrect complexity analysis, or low confidence, revisit the same underlying concept after a short delay with a different surface story.
