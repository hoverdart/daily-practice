# Calibration Neighbors in a Search Tree (Easy)

A calibration service stores distinct integer calibration keys in a binary search tree (BST). Given a requested target, return the closest stored key at or below the target and the closest stored key at or above it.

Implement `calibrationNeighbors(root, target)` in solution.js. Return a two-element array `[floor, ceil]`; use JavaScript `null` for a missing bound. If the target exists, return it in both positions. Each node is an object `{key, left, right}`; children are nodes or null. An empty tree is null. Do not modify the tree.

## Examples
- Tree with root 12, left 4 (right child 7), right 18 (left child 15), target 8: `[7,12]`.
- Same tree, target 12: `[12,12]`.
- Same tree, target 2: `[null,4]`.
- Empty tree, target 0: `[null,null]`.

## Constraints
- 0 <= number of nodes <= 200,000; the tree is a valid BST with unique keys.
- Keys and target are integers in [-10^9, 10^9].
- The tree may be severely unbalanced; avoid relying on recursion depth.
- Aim for O(h) time and O(1) auxiliary space, where h is the tree height.

Run `node tests.js`. Suggested time: 15–25 minutes.
