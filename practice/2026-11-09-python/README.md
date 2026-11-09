# Monday, November 9, 2026 — Python interview practice

Exactly **three new original interview-style problems**. Work in the starter files; do not read the reference implementations before trying each question.

| Difficulty | Problem | CS61B / interview focus | Suggested time |
|---|---|---|---|
| Easy | Merge Service Windows | Sorting, intervals, sweep invariants | 15–20 min |
| Medium | Smallest Complete Sensor Snapshot | Hash-map frequencies, variable sliding window, multiplicity | 25–40 min |
| Hard / stretch | One Discounted Relay Toll | Directed weighted graphs, Dijkstra, two-layer state-space search | 40–60 min |

## Why these topics? (adaptive review)

The repo's curriculum/cs61b.md and CONCEPTS.md cover sorting, hash maps, graph representations, BFS/shortest paths, heap-backed priority queues, and interview extensions such as sliding windows. PROGRESS.md still contains no filled confidence scores.

The most recent **completed** attempts I could verify were on October 5: independent hashing success (5/5), sliding-window frequency-map trouble and a hint (2/5), and an unfinished shortest-path problem (1/5) that required reviewing Dijkstra syntax. Recent November 2–6 attempt files were still unfilled; no improvement was assumed from merely assigning exercises.

Today's easy practices sorting and loop invariants, a break from recent stack/BST easy problems. The medium directly rehearses Python dict frequency bookkeeping and precisely when to shrink a window. The hard restores Dijkstra fluency with an added state variable rather than only a single source-to-target distance.

## Run your attempts

~~~bash
python scripts/run_problem.py practice/2026-11-09-python/easy
python scripts/run_problem.py practice/2026-11-09-python/medium
python scripts/run_problem.py practice/2026-11-09-python/hard
~~~

Starter files deliberately raise NotImplementedError until you implement them. Fill out each attempt.md honestly **before** opening reference/. The tests contain edge cases, deterministic seeded randomized checks against independent small-input oracles, and larger stress cases.

After each attempt, open its reference/notes.md and reference/optimal.py. To validate **all** reference implementations without changing your starter files:

~~~bash
python scripts/check_reference.py practice/2026-11-09-python
~~~

Questions to explain aloud:
1. Easy: Why is sorting enough to prevent a later interval from joining an already-finished merged component?
2. Medium: What does a negative requirement counter mean? When must the missing total increase?
3. Hard: Why do we need two distance values per vertex? Which invariant justifies finishing a Dijkstra state when popped from the heap?

The existing one-time review-guides/graphs-and-cpp-review.md was checked and intentionally not duplicated.
