# Hard / Stretch — Safest Maintenance Route

An industrial campus is modeled as an **undirected, unweighted** graph with `n` stations (0 through n−1) and two-way corridors. Some stations contain hazards.

Define the **safety score** of a station as the fewest corridor hops to **any hazard station**. If no hazard is reachable from that station (including when the hazard list is empty), define its safety score to be **n**. Hazard stations themselves have score 0.

For a route from `start` to `goal`, its **route safety** is the **minimum station safety score encountered**, including both endpoints. Choose a route that **maximizes this minimum**. Return that maximum route safety, or `-1` if no route exists.

Implement:

~~~python
def safest_route(
    n: int,
    edges: list[tuple[int, int]],
    hazards: list[int],
    start: int,
    goal: int,
) -> int:
    ...
~~~

### Examples

1. `n=5`, corridors `[(0,1),(1,2),(2,3),(3,4)]`, hazards `[0]`, start 1, goal 4 → **1**. The unique route has station safety scores 1,2,3,4; its minimum is 1.
2. `n=6`, corridors `[(0,1),(1,4),(4,5),(0,2),(2,3),(3,5)]`, hazards `[4]`, start 0, goal 5 → **1**. Route 0→2→3→5 avoids hazard 4; the route through 4 has safety 0.
3. `n=5`, corridors `[(0,1),(1,2),(3,4)]`, hazards `[4]`, start 0, goal 2 → **5**. No hazard is reachable from the start/goal component, so every station there has safety n=5.
4. `n=3`, corridors `[(0,1)]`, hazards `[1]`, start 0, goal 2 → **-1** (disconnected).

### Constraints and conventions

- `1 <= n <= 100_000`; `0 <= m = len(edges) <= 200_000`.
- Each corridor joins **distinct** valid vertices; undirected corridor pairs are unique.
- `hazards` contains distinct valid vertices, possibly empty.
- `start` and `goal` are valid vertices and may be equal.
- Hazard stations **may** be traversed, but doing so forces route safety to 0.
- Do not mutate inputs. Target **O(n+m + (n+m) log n)** time and O(n+m) auxiliary space.

### Interview questions

1. How do you compute the distance to the **nearest of many** hazards without BFS from each station?
2. Why isn't ordinary shortest-path Dijkstra the right objective for choosing the final route?
3. If a route has safety `s` so far, what is its safety after moving to a station with safety `t`?
4. Why should a **max** priority queue settle the highest current bottleneck score first?
5. What changes if `start == goal` or a whole connected component contains no hazards?
