# Hard / Stretch — Single-Use Transit Voucher

A delivery network has **directed** roads with nonnegative integer tolls. You own a voucher that makes the toll of **exactly one traversed road zero**. You may use it once, and the trip is valid only if you actually use it. Find the minimum total toll to travel from start to goal.

Implement:

~~~javascript
function cheapestVoucherRoute(n, edges, start, goal) {
  // Return minimum toll, or -1 if no valid route exists.
}
~~~

- Vertices are 0 through n-1.
- Each edge is [from,to,toll]. Roads are directed; parallel roads and self-loops are allowed.
- A walk may revisit vertices and roads.
- **Exactly one** edge traversal must consume the voucher, even when start === goal. If no road can be traversed on a valid route, return -1.
- Toll values are integers from 1 to 1,000,000. Costs fit in JavaScript's safe integer range under the constraints.
- Do not mutate the inputs.

**Example 1**

n=4, edges=[[0,1,8],[1,3,5],[0,2,3],[2,3,20]], start=0, goal=3

Output: **3**, taking 0→2 normally (3) and using the voucher on 2→3 (20→0). The alternative 0→1→3 costs 5 with a voucher.

**Example 2**

n=2, edges=[], start=0, goal=0 → **-1**: zero traversals cannot use the voucher.

**Example 3**

n=2, edges=[[0,1,4],[1,0,7]], start=0, goal=0 → **4**: traverse 0→1 normally, then waive 1→0. (Waiving 0→1 instead would cost 7.)

**Constraints:** 1 <= n <= 100,000; 0 <= edges.length <= 200,000. Target **O((n+m) log(n+m)) time** and **O(n+m) space** with a binary min-heap. No third-party packages.

**Optional hint:** Being at vertex v with a voucher and being at v after spending it are *different states*. What transitions connect the two layers?

