# Attempt — Second Distinct Transit Cost

Fill out before opening `reference/`.

- Start / finish / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition and baseline
- Why is this weighted shortest-walk search rather than BFS, MST, or DFS?
- Why is enumerating walks impossible with cycles?
- Why does a single `dist[v]` lose necessary information?

## Heap and distance invariant
- Meaning of `first[v]` and `second[v]`:
- Why must they be strictly different?
- What happens if candidate < first[v]?
- What happens if first[v] < candidate < second[v]?
- Why ignore candidate == first[v]?
- How do I detect stale heap entries?
- Why are positive weights important?
- What happens when source == target?

## Complexity
- Time / space with n vertices, m edges:
- Why is `long long` required?

## Failed tests, hints, C++ syntax friction
- `priority_queue<pair<long long,int>,vector<...>,greater<...>>`:
- Adjacency list / structured bindings / INF:

## After reference
- One Dijkstra invariant to memorize:
- One situation where expanded graph state would be better:
