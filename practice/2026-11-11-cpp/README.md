# Wednesday, November 11, 2026 — C++ Interview Practice

Exactly three original exercises, aligned to the weekday C++ rotation. **Work in solution.cpp first. Do not inspect reference/ until you have attempted a problem and filled in attempt.md.**

| Difficulty | Exercise | Main ideas | Suggested time |
|---|---|---|---|
| Easy | Archive Range Count Queries | Sorted arrays, lower/upper binary-search bounds, C++ iterators | 15–20 min |
| Medium | Longest Trace With Limited Repeated Handoffs | Variable sliding window, unordered-map frequencies, undirected edge keys | 25–40 min |
| Hard / stretch | Rerootable Org Chart Queries | Tree traversal, binary lifting, dynamic-root LCA | 45–65 min |

## Why these are adaptive

The CS61B retention curriculum lists binary search, hashing, BFS/DFS, trees, and asymptotic reasoning; CONCEPTS.md asks for repeated interview-pattern fluency. PROGRESS.md's topic and language confidence tables are not yet filled in. Inspected November 4–10 attempt.md files remain uncompleted templates, so no fresh competency improvement is assumed. Earlier recorded feedback suggested **sliding windows (2/5)** and **shortest paths (1/5)** need more work, whereas hashing was stronger (5/5).

- **Easy:** revisit an underrepresented foundational skill, sorted-array binary search, while practicing real STL syntax and duplicate/off-by-one handling.
- **Medium:** space-repeat the weaker sliding-window concept with a fresh invariant over *undirected handoff edges*, not just frequencies of individual items. This also uses hash maps.
- **Hard:** shift away from the shortest-path-heavy recent stretch set and revisit trees/DFS-BFS from another angle. Root changes introduce a subtle LCA identity and binary lifting, which broaden graph fluency. Shortest-path practice remains a future review priority rather than being declared mastered.

## Run locally

From repository root:

~~~bash
python scripts/run_problem.py practice/2026-11-11-cpp/easy
python scripts/run_problem.py practice/2026-11-11-cpp/medium
python scripts/run_problem.py practice/2026-11-11-cpp/hard
~~~

Starter tests intentionally fail until you implement the functions. To test references **without replacing your starters**:

~~~bash
python scripts/check_reference.py practice/2026-11-11-cpp
~~~

This uses C++17 with g++ -O2 -Wall -Wextra. Each test file includes solution.cpp; the validation script temporarily swaps in reference/optimal.cpp and runs the same deterministic, randomized-oracle, and stress tests.

## Daily reflection checklist

1. Could I define lower_bound versus upper_bound without guessing what equality does?
2. Could I state exactly how many new *repeated handoffs* entering or leaving a window adds/removes?
3. What changes when the rooted tree's root moves? Why doesn't its undirected topology change?
4. For each problem, write naive complexity, optimized complexity, an invariant, and one missed edge case into attempt.md.

## One-time study packet

review-guides/graphs-and-cpp-review.md already exists in the preceding branch and has been preserved unchanged. Do not generate a second copy.
