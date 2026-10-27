# Reference Notes — Timetabled Relay Network

## Recognition signals

Directed stations and links, positive travel durations, and earliest arrival signal shortest paths. The timetable makes edge waiting **time-dependent**; it does not turn the graph into an unweighted graph.

## Brute force versus optimal

For a tiny time horizon, create states (station,time), allow one-unit waiting and scheduled departures, then search reachable states. The time horizon here can be enormous. Instead store the earliest arrival per station. For a link with period p, offset o, and current time t: depart=o if t≤o; otherwise let r=(t-o)%p and depart=t if r=0, else t+(p-r). Candidate arrival is depart+travel. Relax candidates using a min-priority queue.

## Core invariant and proof

best[v] is the smallest arrival time found so far at v. The key FIFO property: the next scheduled departure is a nondecreasing function of arrival time. Arriving earlier can always wait to simulate any later arrival; therefore it never hurts to reach a station earlier. This dominance permits one best arrival per vertex. Dijkstra's first non-stale pop finalizes that station's earliest arrival. Travel≥1 prevents backward-time transitions.

## Complexity

Adjacency-list construction O(n+m). At most O(m) successful relaxations are inserted into the heap; O((n+m)log(n+m)) time and O(n+m) space with a binary heap. In sparse graphs, this is conventionally described as O((n+m)log n). Waiting arithmetic is O(1) per relaxation.

## Common mistakes

- BFS minimizes hops, not arrival time.
- Forgetting to wait until offset, or rounding an exact departure up by a whole period.
- Inserting reverse links in a directed network.
- Using int for arrival times on long paths.
- Marking a node visited on insertion instead of finalization on pop.
- Assuming edge cost is just travel time, ignoring timetable waiting.
- Comparing long heap keys by subtraction, risking overflow.

## CS61B connections

Adjacency lists, heap-based Dijkstra, relaxation, stale priority queue entries, and proof by monotonicity. Contrast with coupon/key-state problems: those require expanded state because resources change future options. Here waiting makes earlier arrival dominate later arrival, so no extra state is needed.

## Follow-up

What changes if stations forbid waiting or links have deadlines? Earlier arrival might no longer dominate all later arrivals; one distance per vertex could cease to be sufficient.
