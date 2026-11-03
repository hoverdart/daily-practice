# Tuesday, November 3, 2026 — Java interview practice

Exactly **three new original interview exercises**, with runnable tests and intentionally incomplete starters. Solve `Solution.java` before opening `reference/`.

| Difficulty | Problem | Focus | Suggested time |
|---|---|---|---|
| Easy | Cumulative Calibration Patches | Difference arrays, prefix sums, long overflow safety | 15–20 min |
| Medium | Longest Window With Limited Handoff Types | Sliding window, HashMap, counting ordered adjacent transitions | 25–35 min |
| Hard / Stretch | Minimum Boot Stations for a One-Way Network | SCCs, iterative Kosaraju, condensation DAG sources | 40–55 min |

## Why these topics?

- The latest **filled-in** October 5 attempts report **hash/set 5/5 (independent)**, **sliding window 2/5 (needed hint; unclear what frequency map counts)**, and **shortest paths 1/5 (unfinished; needed Dijkstra help)**. More recent attempt files through November 2 are largely blank, so they do **not** establish improved proficiency. `PROGRESS.md` topic confidence cells remain unfilled.
- Easy covers array range updates with difference/prefix sums (an under-practiced interview extension of CS61B array/runtime material), rather than another hashing warm-up.
- Medium deliberately revisits a weak **window-frequency invariant**, but counts **directed adjacency types** rather than individual items or ordinary distinct values. It also checks lossless signed-int pair encoding in Java.
- Hard broadens graph traversal skills to **SCCs and source components**, with an iterative implementation that handles deep Java graphs; this complements (rather than duplicates) November 2's 0-1 shortest path exercise. Shortest paths remain a review priority for a later spaced repetition interval.
- Selection is grounded in `curriculum/cs61b.md`, `CONCEPTS.md`, `PROGRESS.md`, and recent `practice/**/attempt.md` files.

## Run / review

From the repository root (Java 17+):

~~~bash
python scripts/run_problem.py practice/2026-11-03-java/easy
python scripts/run_problem.py practice/2026-11-03-java/medium
python scripts/run_problem.py practice/2026-11-03-java/hard

# Validates optimal references in temporary folders, not your starters:
python scripts/check_reference.py practice/2026-11-03-java
~~~

The starter methods intentionally throw `UnsupportedOperationException` and will fail tests until implemented. Each suite contains fixed cases, independent seeded randomized oracles, input-mutation checks, and large cases. After each attempt, fill in `attempt.md` with reasoning, confidence, hints, complexity, and mistakes. Then read `reference/notes.md`.

The one-time comprehensive guide at `review-guides/graphs-and-cpp-review.md` already exists. It was **not recreated or modified**.