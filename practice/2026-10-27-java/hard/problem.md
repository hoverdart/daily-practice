# Hard / Stretch — Timetabled Relay Network

A packet travels through a **directed** network of n relay stations. Every directed link has a timetable: travel time t>0, with departures at times

**offset, offset+period, offset+2·period, ...**

where period≥1 and 0≤offset<period. The packet starts at source at time 0 and may wait at any station. Find the **earliest possible arrival time** at target, or -1 if unreachable.

Implement:

~~~java
public static long earliestArrival(int n, int[][] links, int source, int target)
~~~

Each link row is {from, to, travel, period, offset}. Stations are numbered 0 through n-1. The network is directed: do not add reverse edges.

## Examples

- n=2, link {0,1,3,5,2}, source=0, target=1 → **5** (depart 2, arrive 5).
- n=3, links {0,1,2,4,1}, {1,2,1,5,0}, {0,2,10,1,0} → **6** (reach station 1 at 3, depart at 5, arrive 6).
- n=1, no links, source=target=0 → **0**.
- n=2, no links, source=0, target=1 → **-1**.

## Constraints

1 ≤ n ≤ 100,000; 0 ≤ links.length ≤ 200,000. 0 ≤ from,to,source,target < n. 1 ≤ travel,period ≤ 1,000,000; 0 ≤ offset < period. Parallel links and self-loops may occur. Waiting is allowed. Do not mutate links.

Aim for **O((n+m) log(n+m)) time and O(n+m) space** with a min-priority queue. Explain why BFS is wrong, why it suffices to take the **next** departure on a link, and why Dijkstra-style finalization is valid despite time-dependent waiting.
