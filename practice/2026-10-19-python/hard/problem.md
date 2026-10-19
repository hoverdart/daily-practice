# Hard / Stretch — Repair-Station Relay Route

A delivery robot moves on an **undirected** road network. It must travel from start to goal while visiting **at least one** certified repair station (relay). Each road has a **strictly positive integer** travel time.

Return a triple **(minimum_total_time, chosen_relay, route)**. The route must start at start, end at goal, and contain chosen_relay. If multiple relays can achieve the same minimum time, choose the **smallest relay ID**. Among equally short routes through that relay, any valid route is acceptable. If no valid route exists, return **(-1, -1, [])**.

~~~python
def route_via_relay(
    n: int,
    roads: list[tuple[int, int, int]],
    start: int,
    goal: int,
    relays: list[int],
) -> tuple[int, int, list[int]]:
    ...
~~~

### Examples

- n=5, roads=[(0,1,2),(1,4,2),(0,2,2),(2,4,2)], start=0, goal=4, relays=[2,1] → **(4,1,[0,1,4])**. Both relays tie at 4; choose 1.
- n=3, roads=[(0,1,3)], start=0, goal=2, relays=[1] → **(-1,-1,[])**.
- n=3, roads=[(0,1,2),(1,2,2)], start=0, goal=0, relays=[1] → **(4,1,[0,1,0])**. Returning to start is allowed.

### Constraints

- 1 ≤ n ≤ 100,000; vertices are 0 through n-1.
- 0 ≤ len(roads) ≤ 200,000; no self-loops and no duplicate undirected endpoint pairs.
- All road times are positive integers between 1 and 1,000,000.
- 0 ≤ len(relays) ≤ n; station IDs are valid; duplicate station IDs are allowed.
- start and goal are valid; they may be the same.
- A route is a **walk**: repeated vertices/roads are allowed (necessary if the relay is off the direct path).
- Do not mutate the input. Aim for O((n+m) log n) time and O(n+m) auxiliary space.

### Interview prompts

1. Why isn't ordinary shortest(start, goal) sufficient?
2. For a **fixed** relay r, how can you calculate the best route length?
3. Why can a shortest-path tree from goal reconstruct a relay→goal route on **undirected** roads?
4. How do you skip stale heap entries and reconstruct the two route halves without duplicating the relay?

