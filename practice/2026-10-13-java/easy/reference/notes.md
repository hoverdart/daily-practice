# Reference notes — Deepest Leftmost Sensor

## Recognition signals

The input is a binary tree; the request mentions **depth** and a left-to-right tie-break. Level-order traversal (BFS) visits nodes in increasing depth and, when left children are enqueued first, left-to-right order within each depth. That makes a queue a natural fit. This is **not** a shortest-path-in-a-weighted-graph problem.

## Brute force versus optimal

A naive approach repeatedly searches the tree to find all nodes at depth d, incrementing d until no nodes remain. On a tall tree that can scan the same nodes O(h) times: O(nh), as bad as O(n^2). A single DFS can also be O(n) if it tracks depth and visits left before right, but recursion can overflow on a 100,000-node chain.

The iterative BFS reference uses an ArrayDeque. At the beginning of each outer iteration, the queue holds exactly one depth's nodes in left-to-right order. Freeze levelSize before processing that level; remember the **first** node's value; enqueue each node's left child before its right child. When the queue empties, the remembered value belongs to the deepest level.

## Correctness invariant

All nodes currently queued at the start of a level are at the same depth and are ordered left-to-right. Processing exactly levelSize nodes produces the next level in the same order. The first node at the final nonempty level is therefore deepest-leftmost.

## Complexity

Each node is enqueued and removed exactly once: **O(n) time**. The queue holds at most O(w) nodes for maximum level width w; a skewed tree uses O(1) queue space. A null root returns -1.

## Common mistakes

- Recording the **last** element of each level gives deepest-rightmost.
- Enqueueing right before left reverses the tie-break.
- Iterating while i < queue.size() without freezing levelSize mixes levels because queue.size() changes during traversal.
- Using recursion on a deep chain risks StackOverflowError.
- Confusing node values with depth: negative values are legitimate.

## CS61B connections

Tree traversal, FIFO queues, iterative versus recursive search, and BFS's frontier invariant. Compare with graph BFS: trees have no cross-edges, so you do not need a visited set when traversing child pointers downward.

## Java syntax

```java
Queue<TreeNode> q = new ArrayDeque<>();
q.add(root);
while (!q.isEmpty()) {
    int count = q.size();
    for (int i = 0; i < count; i++) {
        TreeNode node = q.remove();
        if (node.left != null) q.add(node.left);
        if (node.right != null) q.add(node.right);
    }
}
```

If the question changes to deepest-rightmost, choose the last node at each level instead.
