# Attempt — Safest Maintenance Route

Complete **before** opening `reference/`.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Graph recognition and brute force
- What makes this a graph problem?
- What would BFS from every station cost?
- Why would enumerating every simple start→goal route be exponential?

## Multi-source BFS invariant
- Which vertices enter the initial queue?
- What does `danger_distance[v]` mean?
- Why is n a safe sentinel for unreachable hazards?
- Why are hazard distances computed in O(n+m) total?

## Widest-path / heap invariant
- What does `best[v]` represent?
- If the current route score is s and neighbor safety is t, why is the candidate `min(s,t)`?
- Why use a max-heap rather than Dijkstra's min-heap?
- Why can the goal's first non-stale pop be returned?
- What happens if start==goal, or if no hazard can reach this component?

## Claimed time and auxiliary space

## Failed tests, hints, Python deque/heapq syntax friction

## After reference
- One BFS invariant to memorize:
- One priority-queue invariant to memorize:
- How is this different from ordinary shortest paths and minimum spanning trees?
