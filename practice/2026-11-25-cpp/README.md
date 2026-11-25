# Wednesday, November 25, 2026 — C++ Interview Practice

Exactly three original exercises. Work in solution.cpp before opening reference/; complete attempt.md honestly.

| Difficulty | Exercise | Core ideas | Suggested time |
|---|---|---|---|
| Easy | Stable Dispatch Manifest | Stable counting sort, offsets, array invariants | 15–25 min |
| Medium | Longest Calibration Span With One Free Reading | Sliding window, monotonic deque, 64-bit sums | 25–40 min |
| Hard / stretch | Latest Safe Dispatch | Reverse graph, max heap, deadline-aware label setting | 40–65 min |

## Adaptive selection

The inherited curriculum/cs61b.md and CONCEPTS.md include counting/radix sorting, deques, amortized analysis, priority queues and graph relaxation. PROGRESS.md remains unfilled. The October 5 completed attempts recorded 5/5 hashing (independent), 2/5 sliding windows (hint needed for counts and shrinking), and 1/5 shortest paths (unfinished; Dijkstra recognition/API friction). The inspected November 20, 23 and 24 attempts are blank. Assigned practice is not proof of mastery.

- Easy: vary a recent stack/queue-heavy easy sequence with stable integer sorting and C++ std::array. Explain why bounded keys change the cost model.
- Medium: revisit the weaker window pattern without repeating yesterday's equal-pair frequency map or Monday's distinct-count window. The new invariant is sum minus an exact maximum; connect the deque to CS61B and practice long long.
- Hard: reinforce weighted graph recognition after yesterday's second-distance variant, with a different relaxation direction, objective, heap ordering and deadline constraint. Compare the forward feasibility baseline with a single backward search.

## Run from the repository root

```bash
python scripts/run_problem.py practice/2026-11-25-cpp/easy
python scripts/run_problem.py practice/2026-11-25-cpp/medium
python scripts/run_problem.py practice/2026-11-25-cpp/hard
python scripts/check_reference.py practice/2026-11-25-cpp
```

Requires Python 3 and g++ with C++17. Each tests.cpp includes its sibling solution.cpp; the starter is intentionally incomplete. The reference checker substitutes optimal.cpp into a temporary copy and leaves starters intact. Tests include fixed examples, 5,000 seeded randomized cases across the three exercises, and large stress cases. The one-time review packet already exists on main and this inherited branch at review-guides/graphs-and-cpp-review.md; it is left untouched.

## Reflect
Explain stability, monotonic validity, and label-setting in your own words. Record actual confidence and failed cases, not simply completion.
