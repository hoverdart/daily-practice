# Easy — Closest Calibration Threshold

A calibration service stores distinct signed integer thresholds in a nonempty **binary search tree (BST)**. Given a target threshold, return the stored value whose absolute difference from target is smallest. If two values tie, return the **smaller** one.

Every value in a node's left subtree is smaller than the node; every value in its right subtree is larger.

Implement:

~~~java
public static int closestThreshold(Solution.Node root, int target)
~~~

The provided Node has fields value, left, and right.

## Examples

- Tree containing 2, 4, 6, 8; target 5 → 4 (tie).
- Tree containing -9, 1, 12; target 10 → 12.
- Tree containing 42; target -100 → 42.
- Tree containing Integer.MIN_VALUE and Integer.MAX_VALUE; target 0 → Integer.MAX_VALUE.

## Constraints

1 ≤ nodes ≤ 100,000. All values are distinct signed 32-bit integers; target is any signed 32-bit integer. The tree may be highly skewed. Do not mutate it.

Aim for O(h) time and O(1) auxiliary space, where h is tree height. Explain why you can ignore the subtree on the wrong side of the target.
