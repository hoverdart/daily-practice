# Thursday, November 5, 2026 — C Practice

Exactly three original interview-style exercises. Read each problem and try your own solution before looking inside reference/.

| Level | Exercise | Focus | Suggested time |
|---|---|---|---|
| Easy | Stable Triage of a Linked Queue | Singly linked lists; stable in-place relinking | 15–20 min |
| Medium | Count Calm Signal Intervals | Sliding window; two monotonic deques; counting subarrays | 30–40 min |
| Hard / stretch | Mandatory Edges on Every Fastest Route | Two BFS passes; reverse graph; shortest-path layers | 45–60 min |

## Adaptive reasoning

- The CS61B curriculum and CONCEPTS.md specifically call out linked structures, sentinel nodes, circular queues, BFS, graph representations, asymptotic analysis, two pointers, and sliding windows.
- PROGRESS.md still has blank confidence fields, and the recent November 2–4 attempt templates checked are unfilled. Do not mistake an empty template for a completed attempt.
- Older completed attempt feedback indicated sliding windows around 2/5 and shortest paths around 1/5, while hashing was stronger (around 5/5). This is historical information, not a new measurement.
- Easy: revisit pointer invariants in C, a language where losing a link is a real bug.
- Medium: repeat sliding-window reasoning with a different objective: count every valid interval instead of finding one longest/minimum interval. Monotonic deques bring back CS61B array-backed queue reasoning.
- Hard: repeat shortest-path logic, now unweighted BFS instead of Dijkstra; combine forward/reverse distances and a proof about mandatory edges in the shortest-path DAG. No enormous shortest-path counts required.

## Running your solutions

From the repository root:

~~~bash
python scripts/run_problem.py practice/2026-11-05-c/easy
python scripts/run_problem.py practice/2026-11-05-c/medium
python scripts/run_problem.py practice/2026-11-05-c/hard
~~~

Tests intentionally fail until you replace the TODO implementations in solution.c. To validate the untouched reference implementations:

~~~bash
python scripts/check_reference.py practice/2026-11-05-c
~~~

The check_reference script temporarily copies each reference/optimal.c into its matching starter location. Your own solution.c is not modified.

After each exercise fill in attempt.md: time, independent/hint/reference outcome, confidence, complexity, and at least one concrete bug or invariant. Do not open reference/ until after your attempt.

## Discussion checkpoints

1. How do two dummy-head sublists let you rearrange existing linked nodes without allocating or copying nodes?
2. Why does a valid window ending at right contribute exactly right-left+1 intervals?
3. For a shortest s-to-t route of length D, why does it cross each BFS depth boundary exactly once? What does this imply if only one eligible *edge* crosses a particular boundary?

The previously created review-guides/graphs-and-cpp-review.md already exists and is intentionally unchanged; this is not a second review packet.

