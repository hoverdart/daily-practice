# Attempt — Second Distinct Dispatch Arrival

Complete before opening reference/.

- Start / finish / total minutes:
- Outcome (independent / hints / reference / unfinished):
- Confidence (1–5):
- Baseline complexity / optimal complexity and space:
- First failing case or PriorityQueue mistake:
- One concept to revisit in 2–4 days:

## Explain the graph reasoning
- Why not BFS, a single-distance Dijkstra, or DFS enumerating simple paths?
- Precisely distinguish a walk, a simple path, and a distinct cost.
- What do first[v] and second[v] represent while the algorithm is running?
- If a third distinct cost reaches v, why can it never lead to one of the two smallest distinct costs at any downstream vertex via that suffix?
- What happens to the former first when a smaller candidate arrives?
- Why is an equal candidate ignored?
- Why is the former first's heap ticket sufficient after demotion?
- Why is a single visited[v] incorrect?
- When is it safe to return at the target?
- How do positive weights, parallel links, disconnection, and start=target affect the algorithm?
- Relate the proof to CS61B Dijkstra, relaxation, and heaps.
