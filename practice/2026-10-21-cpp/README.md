# Wednesday, October 21, 2026 — Adaptive C++ Practice

Exactly three original interview problems, in C++17:

| Level | Problem | Primary skills |
| --- | --- | --- |
| Easy | Merge Two Calibrated Chains | Linked-list pointers, stable merge, in-place ownership |
| Medium | Longest Low-Collision Window | Sliding window, hash-map frequencies, pair-count invariant |
| Hard | Second Distinct Transit Cost | Directed graphs, Dijkstra, two distances per vertex, heaps |

**Selection rationale.** The last filled-in logs (Oct 5) report hashing 5/5, sliding windows 2/5 (hint), and Dijkstra/shortest paths 1/5 (unfinished). Oct 14–20 attempts are blank; no improvement is assumed. Easy rotates in under-practiced linked-list pointer fluency; medium returns to frequency-map windows with a new invariant; hard revisits weighted shortest paths without repeating the ordinary shortest-route question. This matches curriculum/cs61b.md, CONCEPTS.md, and PROGRESS.md.

**Workflow:** implement each `solution.cpp`, run `python scripts/run_problem.py practice/2026-10-21-cpp/easy` (substitute medium/hard), record `attempt.md` *before* opening `reference/`. To check the references run `python scripts/check_reference.py practice/2026-10-21-cpp`. The starter is intentionally unfinished; the reference is expected to pass.

The one-time `review-guides/graphs-and-cpp-review.md` already exists and was left untouched.
