# Easy — Closest Shared Supervisor

A company's reporting structure is a **rooted forest**. Employee `i` reports to `parent[i]`; a value of `-1` means the employee is a root. Every employee has at most one direct supervisor, and there are no cycles.

For two employees `a` and `b`, find their **lowest common ancestor**: the shared supervisor (including either employee themself) that is closest to them in the reporting hierarchy. If they belong to different trees, return `-1`.

Implement:

```javascript
function closestSharedSupervisor(parent, a, b) {
  // Return employee ID or -1.
}
```

**Input:** `parent` is an array of length `n`, with `1 <= n <= 200000`. Every entry is `-1` or a valid different employee ID. The directed parent links form a forest; employee IDs **are not necessarily ordered by depth**. `a` and `b` are valid indices.

**Output:** one integer, the lowest common ancestor or `-1`. Do not mutate `parent`.

**Examples:**

```
parent = [-1,0,0,1,1,2,-1,6]
a=3, b=4 -> 1
a=3, b=5 -> 0
a=3, b=7 -> -1
a=2, b=2 -> 2
```

**Target:** `O(h_a + h_b)` time, `O(h_a)` auxiliary space, where `h_x` is the number of vertices on x's ancestor chain. Avoid recursion so a 200,000-node chain is safe.

**Optional hint:** Collect every ancestor of one employee, then climb the other employee's chain until you find the first match.
