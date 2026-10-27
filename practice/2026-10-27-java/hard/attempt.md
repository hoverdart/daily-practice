# Attempt — Timetabled Relay Network

Complete **before** opening reference/.

- Started / finished / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition
- Why is this directed weighted shortest path rather than BFS or MST?
- What does each adjacency-list entry store?
- Why does a link's effective cost depend on arrival time?

## Brute force versus optimal
- How could a time-expanded graph model waiting and departures?
- Why is time expansion too large at full constraints?
- How can I find the next departure without simulating every time unit?

## Dijkstra invariant
- What does best[u] mean?
- Why is taking a later departure on the same link never better?
- Why can an earlier arrival always imitate a later one by waiting?
- Why is the first non-stale min-heap pop final?
- Why use long and skip stale entries?

## Java and reflection
- PriorityQueue<long[]> comparator:
- Time in n stations and m links:
- Auxiliary space:
- Failed tests / hints / syntax friction:
- One transferable graph recognition signal:
