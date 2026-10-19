# Attempt — Repair-Station Relay Route

Complete **before** opening reference/.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Graph representation and recognition
- What does one adjacency-list entry mean?
- Why is this weighted shortest path rather than BFS or MST?

## Brute-force idea → two-Dijkstra reduction
- What is the optimal distance through fixed relay r?
- Why are two runs enough, regardless of number of relays?
- How do I break ties on relay ID?

## Dijkstra invariant / parent reconstruction
- What is in each heap entry?
- When is an entry stale?
- How do I recover start→relay and relay→goal?
- What happens if start == goal or a relay is disconnected?

## Claimed time / extra space

## Failed tests, hints, Python heapq/API friction

## After reference
- One invariant I want to memorize:
- One graph recognition signal for next time:

