# Explanation — Calibration Neighbors in a Search Tree

## Recognition signals
"At or below" and "at or above" mean floor and ceiling, not absolute nearest. The input is already a BST, so use its ordering rather than sorting or treating it as an arbitrary binary tree.

## Baseline to optimal
A full traversal with two running extrema takes O(n) time and O(h) call-stack or explicit-stack space. Flattening then sorting is unnecessary; inorder traversal already produces sorted keys, but still visits every node. Binary search on that flattened array would require O(n) preprocessing.

Instead maintain lower/upper candidates and walk exactly one child per step. At a node below target, the node is a valid floor and every key in its left subtree is smaller; only the right subtree could improve the floor or supply a ceiling. At a node above target the argument is symmetric. Equality immediately resolves both.

## Invariant and example
At the start of each step, lower and upper are the best respective candidates among relevant eliminated regions; any strictly better candidate must be in the current subtree. For target 8 in the example, 12 sets upper, 4 sets lower, 7 improves lower, then a null right child proves [7,12]. Each move preserves the invariant and removes one level.

## Complexity
O(h) time, O(1) auxiliary space. Balanced trees give O(log n); a chain gives O(n). A comparison search may have to visit every level in the worst case, so the bound is tight. Output has constant size.

## Common mistakes
- Returning only one neighbor or excluding exact equality.
- Using zero as a missing marker (zero is a valid key).
- Replacing both candidates at each node or walking both children.
- Claiming O(log n) without a balance assumption; recursive JavaScript can overflow on skewed trees.
- Mutating tree links while searching.

## CS61B connection
BST ordering, comparison-based search, tree height and balanced-tree motivation (B-trees), and reference types. The floor/ceiling invariant parallels lower/upper-bound searches in a sorted array, but the next search region is represented by child references.

## Transfer
How would you return strictly smaller/greater neighbors instead? How would your approach change if the input were an arbitrary binary tree?
