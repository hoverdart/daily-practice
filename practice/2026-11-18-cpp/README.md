# Wednesday, November 18, 2026 — C++ Interview Practice

Three original exercises, one easy / medium / hard-stretch. **Implement in solution.cpp before reading reference/**. Complete each attempt.md after coding.

| Difficulty | Exercise | Main ideas | Suggested time |
|---|---|---|---|
| Easy | Package Prefix Inventory | Tries, character-indexed children, prefix multiplicity | 15–25 min |
| Medium | Minimum Calibration Group Span | Binary search on answer, greedy partition, monotonic feasibility | 25–40 min |
| Hard / Stretch | Critical Firmware Rollout Chains | Topological sort, forward/backward DAG DP, critical paths | 40–65 min |

## Why today's choices are adaptive

- curriculum/cs61b.md identifies tries, binary search, DAG topological sorting, shortest paths, and complexity arguments as retention goals. CONCEPTS.md lists tries and binary-search-on-answer among interview targets.
- PROGRESS.md has unpopulated confidence tables. The latest reviewed November attempt.md files remain blank; do **not** infer success from their presence.
- The last filled October 5 assessments marked hashing 5/5, sliding window 2/5 (with a hint), and shortest paths 1/5 (unfinished). Recent days have repeatedly revisited sliding windows (including yesterday), so today gives that exact pattern a spacing interval while strengthening new recognition skills.
- **Easy:** a trie has not been practiced much recently; explicit character transitions and duplicate counts reinforce CS61B trees and C++ vector/reference safety.
- **Medium:** a monotonic feasibility check uses a left-to-right greedy scan, extending the pointer-invariant intuition from windows into binary search on answer. 64-bit boundary arithmetic matters.
- **Hard:** build on weaker path-relaxation reasoning and DAG knowledge without assigning another ordinary Dijkstra variant. Two dynamic-programming passes identify **every** task and prerequisite edge that belongs to at least one longest dependency chain, including ties and zero-duration tasks.

## Running the practice

From repository root with g++ (C++17) and Python 3:

~~~bash
python scripts/run_problem.py practice/2026-11-18-cpp/easy
python scripts/run_problem.py practice/2026-11-18-cpp/medium
python scripts/run_problem.py practice/2026-11-18-cpp/hard

# Validate reference solutions without overwriting the starters:
python scripts/check_reference.py practice/2026-11-18-cpp
~~~

Each test includes its sibling solution.cpp, so **starter tests intentionally fail** until implemented. The reference checker copies the problem to a temporary directory and substitutes reference/optimal.cpp. Tests cover deterministic edge cases, seeded small randomized checks against a separate brute-force oracle, and large stress cases. Run your own tests, record outcomes/confidence/complexity in attempt.md, and then inspect the reference.

## Post-practice reflection

1. What information belongs in a trie's node versus on its incoming edge?
2. Why is "can partition with span <= X" monotone in X, and why is the greedy split optimal for that X?
3. What do the two DP arrays mean in the critical-chain problem? Why does combining their values detect membership on *some* maximum-length path?
4. What specifically still feels weak from graph path algorithms and sliding windows? Use concrete counterexamples in attempt.md.

## One-time review guide

The existing review-guides/graphs-and-cpp-review.md was verified on main and deliberately left unchanged. No duplicate review packet is generated.
