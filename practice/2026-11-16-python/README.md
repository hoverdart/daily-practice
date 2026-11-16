# Monday, November 16, 2026 — Python Interview Practice

Three original interview-style exercises. Solve each unfinished **solution.py** before viewing **reference/**.

| Difficulty | Problem | Primary pattern | Suggested budget |
|---|---|---|---|
| Easy | K-th Highest Incident Priority | Size-k min-heap, streaming top-k | 15–25 minutes |
| Medium | Longest Consensus Segment | Sliding window, stale maximum, hash-frequency invariants | 25–45 minutes |
| Hard / stretch | Farthest Critical Server in a Tree | Two-pass tree DP, iterative traversal, rerooting | 45–70 minutes |

## Adaptive selection

The source of truth is the inherited repository's **curriculum/cs61b.md**, **CONCEPTS.md**, **PROGRESS.md**, and the recent **practice/** attempt records inspected through November 13. The progress confidence table has no scores, and recent attempts (including November 9, 10, 11, 12, and 13) are still unfilled templates; do not mistake assigned exercises for demonstrated mastery. Earlier recorded feedback favored hashing over sliding-window and shortest-path recognition.

- Easy: Return to CS61B binary heaps and top-k streaming rather than yet another hash lookup, queue, or disjoint set.
- Medium: Spaced repetition for sliding-window frequency invariants, using the different **make-everything-equal with k changes** constraint and a subtle cached-max proof. Contrast the last signed-prefix-sum exercise: here moving the left boundary is valid because a window's mismatch count can only improve after removing elements.
- Hard: Switch from repeated shortest-path Dijkstra problems to weighted tree DFS and reroot dynamic programming. It still strengthens graph representation, parent relationships, and iterative traversal while introducing reusable tree DP.

## Workflow

1. Read **problem.md**; explain a brute-force idea and its complexity before coding.
2. Fill out **solution.py** only; run the test harness.
3. Record failures, hints, recognition signal, and a truthful confidence score in **attempt.md**.
4. Unlock **reference/notes.md** and **reference/optimal.py** only after the attempt.

From repository root:

~~~bash
python scripts/run_problem.py practice/2026-11-16-python/easy
python scripts/run_problem.py practice/2026-11-16-python/medium
python scripts/run_problem.py practice/2026-11-16-python/hard
python scripts/check_reference.py practice/2026-11-16-python
~~~

The reference-validation command substitutes a reference into a temporary copy and **does not** complete your starter. Tests use fixed edge cases, deterministic independent random oracles, and large stress examples.

The one-time graph/C++ review already exists at **review-guides/graphs-and-cpp-review.md** in the source branch and is deliberately not duplicated.
