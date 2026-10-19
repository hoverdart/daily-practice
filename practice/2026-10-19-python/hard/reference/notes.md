# Repair-Station Relay Route — Reference Notes

## Recognition signals
Weighted undirected roads with **strictly positive** weights → Dijkstra. A mandatory waypoint means the direct shortest start→goal route is not necessarily feasible. The question asks for the **actual route**, so distance arrays alone are insufficient; keep parent/edgeTo arrays.

## Brute force → optimal
Naive: run a shortest-path search from start to each relay and from that relay to goal; O(R (V+E) log V) with R stations. This repeats most work.

For any fixed relay r, every valid walk visiting r can be split into a start→r part and an r→goal part. Its minimum length is **dist(start,r) + dist(r,goal)**. Two Dijkstra runs, rooted at start and goal, provide these values for **every relay** at once. Scan relays and select min of (total_cost, relay_id) so ties choose the smallest ID.

Why two Dijkstra runs? Because roads are **undirected**. Dist(goal,r) equals dist(r,goal). In a directed graph you would need a run from goal on the **reversed** graph for the second half.

## Dijkstra invariant and heap details
- Initialize distance[source]=0 and all other distances to infinity.
- Heap entries are (tentative_cost, vertex), so Python heapq is a **min-heap** by cost.
- Pop the smallest tentative state. If popped_cost != distance[vertex], skip stale entries; a better path was already found.
- For each neighbor, relax if cost+weight < distance[neighbor], then update its parent and push a new heap entry.
- Positive weights ensure a settled shortest distance cannot later be improved.

**Important:** Keep parents from **both** runs. The start-rooted parent tree gives start→relay after reversing the chain from relay. The goal-rooted parent tree gives relay→goal by following parent pointers **forward toward goal**. Append nodes after stepping to parent so the relay is not duplicated at the join.

## Walkthrough
For 0—(2)—1—(2)—4 and 0—(2)—2—(2)—4, both stations 1 and 2 have distance 4 through them. Tuple min chooses station 1. The start-rooted chain to 1 is [1,0] → reverse [0,1]; the goal-rooted chain from 1 appends 4; final route [0,1,4].

If start==goal and the chosen relay differs, the route can legitimately go out and return. If no relay is reachable from both endpoints, return (-1,-1,[]).

## Complexity
Let V=n, E=len(roads), R=len(relays). Building adjacency lists takes O(V+E) time/space. Two binary-heap Dijkstra runs take O((V+E) log V) time in the standard bound and O(V+E) auxiliary space including adjacency lists and heap entries. Relay scan is O(R), route reconstruction O(V) per half because positive weights and strict improvements produce acyclic parent chains. Overall O((V+E) log V + R) time, O(V+E) space.

## Common mistakes
- BFS is only for unweighted/equal-weight edges; a priority queue is required here.
- An MST minimizes total network cost, not travel time for a route.
- Running Dijkstra once from start does not give every relay→goal distance in a directed graph; undirected symmetry is crucial here.
- Pushing only vertices into heap instead of (cost, vertex).
- Omitting the stale-entry check or forgetting to update parent when improving a distance.
- Choosing the first relay in the input instead of minimum (cost, ID).
- Appending relay twice when joining the two path halves.
- Assuming start and goal must differ, or assuming a valid walk never revisits a vertex.

## CS61B connections / Python recall
This directly reinforces **graph adjacency lists, priority queues, relaxation, shortest-path trees, and edgeTo/parent reconstruction** from CS61B. Compared with the October 5 shortest-path 1/5 attempt, this adds a deliberate reconstruction step to test whether the underlying algorithm is understood. Python API: import heapq; heapq.heappush(heap, (distance, node)); cost,node = heapq.heappop(heap); float("inf") as unreachable sentinel; min() on tuples breaks ties lexicographically.

