# Thursday, October 8, 2026 — C Practice

**Language:** C11. **Exactly three original problems:** easy, medium, hard/stretch.

## Why these three?

Your completed October 5 attempts show strong hash/set lookup (5/5), but weaker sliding-window frequency accounting (2/5, hint needed) and shortest-path/Dijkstra recall (1/5, unfinished). The October 6 Java and October 7 C++ attempt logs remain blank, so this set does **not** assume those topics have been mastered. The C rotation adds pointers, heap ownership, circular indexing, arrays, and a hand-built priority queue.

1. **Easy — Bounded Dispatch Ring:** circular array/queue invariants, `malloc`/`free`, C pointers. ~15–25 min.
2. **Medium — Minimum Audit Window:** a *minimum covering* window, not another longest-at-most-K problem. Count requirements and shrink only while the window stays valid. ~25–40 min.
3. **Hard — Hazard-Budget Courier:** Dijkstra with `(node, risk_spent)` states, directed adjacency lists and a binary min-heap written in C. ~45–75 min.

## Workflow

Read each `problem.md`, edit only its `solution.c`, run the tests, and fill in `attempt.md` **before** opening `reference/`. The starter intentionally fails tests until implemented.

Run a problem from the repository root:

    python scripts/run_problem.py practice/2026-10-08-c/easy

Repeat with `medium` and `hard`. To verify all *reference* implementations:

    python scripts/check_reference.py practice/2026-10-08-c

The tests include deterministic edge cases and seeded randomized checks against independent simple models/oracles. Compile with `-Wall -Wextra` (the runner does). For extra C debugging locally:

    cc -std=c11 -g -O1 -Wall -Wextra -fsanitize=address,undefined tests.c -o tests && ./tests

Run the sanitizer command inside an individual problem directory.

## Review priority

**First:** ring-buffer `head`/`size` invariant and C memory lifetime. **Second:** what the frequency array actually counts when left/right move. **Third:** what the full graph *state* must contain, when to relax, and how to skip stale heap entries.

The one-time graph/C++ review packet already exists at `review-guides/graphs-and-cpp-review.md`; it was intentionally not recreated.
