# Hard / Stretch — Cheapest Compliant Deployment Order

A release engineer must deploy n modules, numbered 0 through n-1, **exactly once each**. Some modules have prerequisites: for every pair [a,b] in prerequisites, module a must finish before module b starts. A deployment order must respect all directed prerequisite edges.

The engineering team can switch between modules, but the transition from module i to the next module j costs switchCost[i][j]. These costs can be asymmetric. Deploying the **first** module has no switch cost.

Implement:

~~~js
function minimumCompliantSwitchCost(switchCost, prerequisites) {
  // minimum total switching cost, or -1 if no valid order exists
}
~~~

Choose a valid deployment order minimizing the sum of costs between consecutive modules. Return **only its minimum total cost**, not the order. If no valid ordering exists (for example, cyclic prerequisites), return -1. If n=0, return 0. Do not mutate inputs.

### Example

switchCost =
~~~js
[
  [0, 8, 1],
  [2, 0, 2],
  [4, 3, 0]
]
~~~

prerequisites = [[0,2]]

Answer: 3, achieved by the order [1,0,2] (cost 2+1). The alternative [0,2,1] costs 1+3=4. A cheaper-looking order that violates 0-before-2 is forbidden.

### Constraints

- 0 <= n <= 15.
- switchCost is an n-by-n matrix of nonnegative integers <= 100,000; diagonal values can be ignored.
- Prerequisite edges contain integers 0 <= a,b < n, and may include repeated edges or a self-edge.
- Answer fits safely in JavaScript Number.
- Target O(n^2 * 2^n + m) time and O(n * 2^n) memory, where m is the number of prerequisite pairs.

### Think first

A topological ordering handles prerequisites, but different valid topological orders have different switch costs. A greedy choice of the cheapest next module can be wrong. What information must a dynamic-programming state remember about **which tasks are finished** and **which task was finished last**?
