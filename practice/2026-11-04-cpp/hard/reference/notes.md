# Hard — Reference reasoning

## Recognition signals

This is a directed, **nonnegative weighted shortest-path** problem with many candidate meeting points. The phrase **two independent starting points, choose a hub, share a final leg** suggests computing distances from each starting point and to a common destination rather than searching independently for each hub.

Let dA[v] be shortest time A→v, dB[v] be shortest time B→v, dT[v] be shortest time v→T. Synchronization at v occurs at time max(dA[v],dB[v]) because both depart at time 0 and may wait. Earliest arrival through v is:

~~~text
candidate(v) = max(dA[v], dB[v]) + dT[v]
~~~

Only evaluate **allowed hubs** where all three distances are finite.

## Brute force → improved → optimal

A naive solution enumerates each hub and runs shortest path from A, B and the hub to T: up to O(H (V+E) log V) for H hubs, doing redundant work.

Do just **three** Dijkstra searches:
1. From A over forward directed edges; returns all dA[v].
2. From B over forward directed edges; returns all dB[v].
3. From T over the **reversed directed graph**; distance T→v in reverse equals distance v→T in original.

Now scan hubs in any order and minimize candidate(v), breaking ties by smaller ID. The reverse trick matters: a forward search from T computes T→v, which is generally *not* v→T.

## Correctness / invariant

Dijkstra's settled-distance invariant holds for nonnegative edge weights (including zero). Thus each d array contains the minimum travel time for its direction. For any feasible complete plan through hub v, courier A spends at least dA[v], courier B at least dB[v], and their shared final route spends at least dT[v]; hence arrival is at least candidate(v). Choosing three shortest routes and waiting if necessary realizes that bound. Taking the minimum over allowed hubs is therefore globally optimal. Inspect the numeric hub ID on equal times for deterministic tie-breaking.

## Complexity

Building forward and reverse adjacency lists: O(V+E) time/space. Three binary-heap Dijkstra searches: O((V+E) log V) time, O(V+E) extra heap/adjacency/distance space. Checking hubs: O(H), where H≤V. Overall O((V+E) log V) time and O(V+E) space. Disconnected graphs return {-1,-1} when no feasible hub exists.

## C++ / CS61B connections

~~~cpp
using State = std::pair<long long,int>; // (distance, node)
std::priority_queue<State,std::vector<State>,std::greater<State>> pq;
pq.push({0,source});
// Pop min: auto [dist,node]=pq.top(); pq.pop();
~~~

- **Graph representation:** vector<vector<pair<int,long long>>> is a directed weighted adjacency list.
- **Heap:** the default priority_queue is a max-heap; use greater<State> for minimum first.
- **Relaxation:** update dist[v] if dist[u]+weight < dist[v]. A popped pair whose distance differs from dist[u] is stale.
- **Reverse graph:** for original road from→to, store reversed road to→from with same travel time.
- **64-bit:** store distances and max+sum in long long; int can overflow on many edges.
- **Unreachable:** only consider nodes with finite values in all three arrays.
- **Zero weights:** valid for Dijkstra, even with zero-weight cycles.
- **Negative weights:** invalidate the Dijkstra settled-distance proof; don't use this solution if negatives are permitted.
- **Tie-break:** hubs need not be sorted and may be repeated. Update on lower arrival or equal arrival with smaller ID.

### Interview contrast

BFS solves unweighted minimum hops. Dijkstra solves nonnegative weighted travel. Reverse traversal is not about reversing a path physically; it is a computational way to obtain *every node's distance to one fixed destination*. This technique recurs in detour optimization, meeting-point graphs, and evaluating optional waypoints.
