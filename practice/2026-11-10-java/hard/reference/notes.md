# Reference notes — Evacuate the Flooded Relay Station

## Recognition signals

The prompt has **a spreading hazard**, **multiple simultaneous sources**, **unit-duration movements**, and a **one-use traversal resource**. That suggests two unweighted BFS passes: (1) flood deadlines using **multi-source BFS**, (2) shortest safe human path using **BFS on expanded states**. This deliberately revisits the previously missed shortest-path search concept without another Dijkstra heap.

## Baseline vs optimal

- Naive search: enumerate all potential walking routes, simulate flooding for each, and track gate use. The number of walks can grow exponentially with route length; cycles create infinitely many candidate walks unless pruned.
- A wasteful intermediate: run a flood BFS separately for every F source, then take minimum distances. With f sources this takes O(fRC) in the worst case.
- Optimal: put **all** F tiles in one queue with time 0. Unweighted BFS first reaches each traversable cell at the earliest flooding time, O(RC). Then BFS the human over at most **2RC** states: (cell, usedGate in {0,1}). Each move costs 1; check deadline and gate use before enqueueing.

## Exact deadline condition

If floodAt[next] is -1, flood never reaches next; entry is safe at any minute. Otherwise entering next after one more move is legal precisely when **currentTime + 1 < floodAt[next]**. Equality is **unsafe**. You may depart a tile as it floods because the rule checks destination safety at the new minute and current tile was safe at the previous minute.

The flood treats G as traversable; the **human's** permit has no effect on flood propagation.

## Critical state invariant

Human state ID = 2*(r*cols+c) + usedGate. dist[state] is the earliest minute the human reaches that location **safely** with exactly usedGate gate entries. Two states at the same position can have different future options, so one visited flag per cell is incorrect. Within the **same** full state, an earlier arrival is never worse: the flood only expands, never recedes; later arrival cannot unlock an earlier-safe destination. Therefore marking when enqueueing is valid.

As all walking transitions cost 1, FIFO BFS explores states in nondecreasing arrival minutes. Returning when E is first dequeued yields the minimal safe number of minutes.

## Complexity

At most RC flood vertices with <=4RC neighbor inspections, then <=2RC human states with <=8RC neighbor inspections. Both time and auxiliary space are **O(RC)**. The grid is read-only. Integer arrays encode cells and states without allocating a separate object for each queue entry.

## Java implementation reminders

~~~java
int id = r * cols + c;
int r = id / cols, c = id % cols;
int state = 2 * id + usedGate;
int usedGate = state & 1;
Arrays.fill(floodAt, -1);
int[] dr = {1, -1, 0, 0};
int[] dc = {0, 0, 1, -1};
~~~

## Common mistakes

- Starting flood BFS from only one F rather than all F at time 0.
- Treating G as a flood barrier (gates slow the human only).
- Testing arrival <= floodAt rather than strictly less.
- Using visited per cell instead of per (cell, permitUsed).
- Counting distinct gates encountered instead of **entries**, or accidentally reusing the one-time permit.
- Marking a human state visited **before** confirming safety at the arrival time.
- Forgetting the case of zero F sources: all flood times remain -1.
- Using Dijkstra when all movement costs are unit weights; that adds unnecessary logarithmic overhead.

## CS61B connections

Graph representations: implicit 4-neighbor adjacency lists, integer-encoded vertices, distance and visited arrays. BFS queue-layer invariant for shortest unweighted paths. Multi-source BFS computes a minimum distance to any source in one traversal. State expansion is like adding a small bit of history to every graph vertex: compare to shortest paths with a coupon, keys, or remaining wall-break budget. Here the twist is that a second BFS first computes **arrival deadlines**, not a shortest path for the human.
