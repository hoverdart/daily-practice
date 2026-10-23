# Friday, October 23, 2026 — JavaScript

Three **original** interview exercises. Start with the statement and your starter solution; do not open reference/ until you have made a serious attempt.

| Level | Problem | Main practice | Suggested time |
| --- | --- | --- | --- |
| Easy | Insert a Maintenance Window | Sorted intervals, two pointers, linear merging | 15–20 min |
| Medium | Shortest Required-Signal Window | Sliding window, Map frequency deficits, duplicate requirements | 25–35 min |
| Hard / Stretch | Single-Use Transit Voucher | Weighted directed graph, two-layer Dijkstra, custom min-heap | 40–55 min |

## Why these topics?

- Your completed Oct 5 attempts recorded **2/5 sliding-window confidence** and confusion about what a frequency dictionary represents; the medium changes the task from longest valid window to **shortest window covering a multiset**.
- Your Oct 5 shortest-path attempt recorded **1/5 confidence**; the hard returns to nonnegative weighted paths but adds a *coupon-used* state and a JavaScript binary min-heap.
- Your completed Oct 5 hashing exercise was **5/5**; the easy instead checks a less-practiced **sorting/interval merging** pattern tied to CS61B merge-sort reasoning.
- Recent attempt templates (including Oct 19–22) are mostly unfilled; do **not** interpret an unfilled template as mastery or failure.

## Run

From the repository root:

~~~bash
python scripts/run_problem.py practice/2026-10-23-javascript/easy
python scripts/run_problem.py practice/2026-10-23-javascript/medium
python scripts/run_problem.py practice/2026-10-23-javascript/hard
~~~

The starter files deliberately throw TODO errors. After attempting, fill in attempt.md, then compare with reference/notes.md and reference/optimal.js. To verify references without modifying your work:

~~~bash
python scripts/check_reference.py practice/2026-10-23-javascript
~~~

Each tests.js uses deterministic cases, seeded randomized comparisons with a separately written brute-force oracle, and a larger stress case.

