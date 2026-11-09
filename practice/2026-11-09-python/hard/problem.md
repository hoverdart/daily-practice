# Hard / Stretch — One Discounted Relay Toll

A network has n routers numbered 0 through n-1 and a collection of **directed** links. Link (u, v, toll) can be traversed from u to v for a nonnegative integer toll; the reverse direction is not implied.

You have **one optional discount coupon**. On at most one traversed link, you may replace its toll w with floor(w / 2). All other traversals cost their regular toll. You may use the coupon on **any** link of your route, including a zero-cost link, or not use it at all.

Write:

~~~python
def minimum_coupon_route(
    n: int, edges: list[tuple[int, int, int]], source: int, target: int
) -> int:
    ...
~~~

Return the smallest possible total toll from source to target, or -1 if no directed route exists. The coupon applies **once to one traversal**, not once per type of link or once per router.

### Example

~~~text
n = 4
edges = [(0, 1, 9), (1, 3, 7), (0, 2, 3),
         (2, 3, 20), (0, 3, 30)]
source = 0
target = 3

answer = 11
~~~

Path 0 -> 1 -> 3 costs floor(9/2) + 7 = 4 + 7 = 11. A different path 0 -> 2 -> 3 with the coupon on its final link costs 3 + 10 = 13.

### Constraints

- 1 <= n <= 100,000, 0 <= len(edges) <= 200,000.
- 0 <= u, v, source, target < n.
- 0 <= toll <= 10^9.
- Parallel links and self-loops are allowed.
- source may equal target; then the answer is 0.
- Target O((n+m) log(n+m)) time and O(n+m) space with a binary heap.

### Think first

Plain BFS minimizes the number of links, not toll. Running ordinary Dijkstra with just one distance per router is also insufficient: arriving cheaply at a router **after spending the coupon** may be less useful than arriving more expensively **with the coupon still available**.

What would a vertex in an **expanded graph of states** have to record? How many outgoing transitions should each original link create?
