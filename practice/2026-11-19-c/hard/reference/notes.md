# Reference Notes — Fewest Turns for a Grid Relay

## Recognition signals

A grid is a graph even without an explicit edge list. Cost is **not distance traveled**: going straight costs 0, turning costs 1. More subtly, arrival direction changes the future action cost, so a vertex is `(cell, direction)`, **not** merely `cell`. This is a state-space graph with `4 × rows × cols` vertices and at most four outgoing edges per state. Since every edge weight is either 0 or 1, **0–1 BFS** can replace a general priority queue.

## Baselines and improvement

Exhaustively enumerate walks and score their turns: exponential without careful bounds; cycles create unbounded walks. Ordinary BFS optimizes step count, not turn count. Dijkstra over four-directional states is correct at O(RC log(RC)) time with a binary heap, but it ignores the special binary weights. 0–1 BFS uses a deque: push a zero-cost improved state at the **front** and a one-cost improved state at the **back**. It yields O(V+E) = O(RC) time and O(RC) auxiliary space here.

## Invariant and correctness

For the expanded state graph, `dist[s]` is the best discovered cost to s. The deque processes ticket distances in nondecreasing order; a newly relaxed 0-edge state belongs before 1-edge states, while a 1-edge state belongs behind all current tickets of smaller cost. Stale tickets are ignored by comparing the queued distance to `dist[s]`. Therefore the first non-stale popped destination-direction state has globally optimal turn cost. Initializing all four direction states of (0,0) with distance 0 means the first actual move has a free matching direction. This avoids a misleading special “no heading” fifth state.

The grid's best answer is the minimum over four arrival-direction states at the destination. Early exit on first non-stale popped destination ticket is valid for 0–1 BFS. A 1×1 open grid returns zero; an unreachable destination leaves no ticket to pop and returns -1.

## Runtime and C implementation

Each directional state has at most four neighbors. With binary edge weights and strict improvements, standard 0–1 BFS takes O(V+E); since E = O(V), O(RC) time and O(RC) auxiliary memory. The graph adjacency is *implicit*; generate four moves with displacement arrays rather than constructing every edge. Queue storage may need to grow due to duplicate tickets before stale ones are popped. This implementation uses a dynamically growing circular array, copies tickets in logical order on growth, and frees the old buffer. Capacity doubles, so the total copying work is amortized linear in the number of queued tickets.

## Common mistakes

1. Using only `visited[row][col]` and discarding a better orientation at the same cell.
2. Charging the first move for turning from a fake initial direction.
3. Using ordinary FIFO BFS even though edges have different 0/1 weights.
4. Using negative offsets with unsigned row/column indices, causing wraparound.
5. Forgetting the deque's circular-index rotation during growth; copying physical storage in raw order corrupts the queue.
6. Marking a state permanently seen *when enqueuing*: 0–1 BFS must allow a lower-cost re-relaxation.
7. Failing to skip stale tickets, or returning the cost from a stale destination ticket.
8. Recursion on a 200k-cell corridor, or returning without freeing both distance and queue buffers.

## CS61B connections

Graph modeling, BFS, Dijkstra relaxation, graph shortest-path invariants, deque implementation, amortized resizing, and treating “physical location + resource/history” as a state. This differs from prior coupon/layered graph tasks because binary weights admit a more efficient deque-based algorithm.

## Compact pseudocode

```text
dist[(start, all 4 directions)] = 0, push all
while deque not empty:
    ticket = pop_front
    skip if ticket's cost != dist[ticket.state]
    return cost if at destination
    for each valid next direction:
        cost = (direction changed ? 1 : 0)
        if candidate improves dist[next_state]:
            update dist
            push_front for cost 0, push_back for cost 1
return -1
```
