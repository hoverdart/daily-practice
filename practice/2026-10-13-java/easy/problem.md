# Easy — Deepest Leftmost Sensor

A monitoring network is a binary tree of sensors, each holding an integer ID. Return the ID of the sensor at the greatest depth. Break ties by choosing the **leftmost** sensor at that depth.

Implement `public static int deepestLeftmost(TreeNode root)`. The TreeNode class is supplied in Solution.java. Return -1 for a null root; negative sensor IDs are valid. Do not modify the tree.

Example:

```text
        10
       /  \
     20    30
    /        \
   40         50
```

Return 40. If 50 gains a left child with ID 60, return 60.

Constraints: 0 to 100,000 nodes; trees may be highly skewed.

Target: O(n) time and O(w) auxiliary space, where w is maximum level width. Use iterative BFS with a queue; enqueue left before right. Explain what the queue contains at each level and why the first node of the last level is the answer.
