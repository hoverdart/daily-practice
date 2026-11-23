# Monday, November 23, 2026 — Python Interview Practice

Three original exercises. Work in the **unfinished `solution.py`** files; keep `reference/` closed until you have tried each problem and recorded your attempt.

| Difficulty | Problem | Pattern | Suggested time |
| --- | --- | --- | --- |
| Easy | Closest Repair Hub by Hops | Multi-source BFS, deque, distance arrays | 15–25 min |
| Medium | K-Signature Window Budget | Exactly-K via two at-most sliding windows, hash frequencies | 25–45 min |
| Hard/stretch | Maximum Unique Rewards from Start to Exit | SCCs, iterative Kosaraju, condensation DAG DP | 45–75 min |

## Adaptive selection

Selection was based on `curriculum/cs61b.md`, `CONCEPTS.md`, `PROGRESS.md`, and filled/unfilled `practice/**/attempt.md` files through November 20. The progress topic table is still blank. Recent November 16–20 attempts are unfilled, so they do **not** count as mastery. The last completed October 5 self-assessment reported hashing **5/5**, sliding-window bookkeeping **2/5 with hints**, and shortest-path recognition **1/5, unfinished**.

- **Easy:** explicitly practice shortest-hop graph recognition and a Python `collections.deque`. Multiple sources all enter the BFS queue at distance zero; do not run Dijkstra or one BFS per repair hub. This revisits graph-path basics without repeating the weighted-path exercises on November 19–20.
- **Medium:** bring back a genuine weak point: counting and deleting hash-map frequencies when both ends of a sliding window move. Exactly-K counting demands an **at-most(K) minus at-most(K−1)** argument, while the new maximum-length budget adds a second invariant. The goal differs from recent longest or shortest valid windows.
- **Hard:** strengthen directed-graph reachability, DFS finishing order, and DAG reasoning with **positive/zero one-time rewards**. Revisited vertices matter, so neither ordinary shortest paths nor a simple vertex-visited DFS can solve the optimization. Contracting strongly connected components exposes a linear-time DAG DP.

## Run and reflect

~~~bash
python scripts/run_problem.py practice/2026-11-23-python/easy
python scripts/run_problem.py practice/2026-11-23-python/medium
python scripts/run_problem.py practice/2026-11-23-python/hard

# Validate optimal references without modifying starters:
python scripts/check_reference.py practice/2026-11-23-python
~~~

The starter tests are intentionally expected to fail until you implement each `solution.py`. Tests include hand-calculated examples, independent randomized oracles, and large stress cases. Keep each `attempt.md` honest; note hints and mistakes for future spaced repetition.

The one-time `review-guides/graphs-and-cpp-review.md` already exists on the inherited branch. It was **not recreated or modified**.
