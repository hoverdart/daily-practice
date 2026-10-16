# Keycard Escape Maze — reasoning and CS61B connection

## Recognition signals
A grid is an implicit graph: walkable cells are locations, legal moves are edges. But *the set of legal future moves depends on collected keys*. The complete state is **(row, col, keysMask)**, not merely (row,col). This is a classic "secret graph" problem and directly revisits the previously weak shortest-path topic with a simpler unit-weight algorithm.

## Brute force → optimal
A naive DFS that tries all possible walks may loop forever or explore exponentially many routes. A BFS with only a 2D visited array is **incorrect**: arriving at the same junction without a key and then returning with the key are distinct states. You could run a general Dijkstra over expanded states, but every step costs exactly 1, so BFS is simpler and linear in state graph size.

Represent a collected subset using 4 bits: `a -> 1<<0`, `b -> 1<<1`, etc. Door `A` is enterable iff `mask & (1<<0)` is nonzero. Key collection is `nextMask = mask | bit`. Never clear a key bit.

## BFS invariant / proof sketch
Enqueue `(start, 0, 0)` and mark its full state visited immediately. FIFO order guarantees that when a state is first enqueued, the recorded step count is minimal among all paths to **that exact (cell,mask)**. Every edge increases distance by 1. Generate up to four neighbors, reject walls/locked doors, collect keys, and enqueue unseen full states. Therefore the first dequeued exit state has the globally shortest valid escape path. If the queue empties, no reachable exit state exists.

An array plus a moving `head` index implements an efficient JS queue: avoid `Array.shift()` because repeated shifts can require moving remaining elements. Flatten states to `(row*cols + col)*16 + mask` for a compact `Uint8Array` visited table.

## Complexity
Let R rows, C columns, K distinct key types (here K=4). There are at most R*C*2^K states, each with <=4 outgoing transitions. Time O(R*C*2^K); space O(R*C*2^K) for visited and BFS queue. K is fixed at 4, but keep the exponential factor explicit when explaining generalizations.

## Common mistakes
- Using visited[r][c] rather than visited[r][c][mask].
- Treating door 'E' as a locked door; here doors are only A–D and E is the exit.
- Forgetting to collect a key **before** constructing the next state.
- Clearing or consuming a key after opening a door (keys are reusable).
- Marking visited only when dequeued, causing duplicate queue entries.
- Returning as soon as a door is found instead of the exit.
- Incorrectly using DFS for minimum number of unweighted moves.
- Confusing numeric bitwise `|` with boolean `||`.
- Forgetting to test revisiting a cell with a **different** mask.

## CS61B connections
BFS and queue invariants; graph representations (implicit adjacency); shortest paths in unweighted graphs; visited/parent arrays; bit manipulation; state-space graph expansion. Extension: if movement costs vary, use Dijkstra over the same expanded states, not ordinary BFS. If you must reconstruct a path, store predecessor **state IDs**, not only predecessor cells.
