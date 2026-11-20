# Attempt — Shortest Incident Evidence Segment

- Started / finished / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute force versus optimal complexity:
- Extra space and Map operations:
- First failed test / off-by-one mistake:

## Sliding-window invariant

- Explain `need`, `have`, and `missing` in one sentence each.
- Why is a multiset different from a set of required codes?
- Why can you increment the left edge only when all required items are present?
- When does removing the leftmost item increase `missing`?
- What exactly happens upon `"#"`? Why must a window not span a barrier?
- Why is it OK to retain unneeded event codes inside the segment?
- Why are half-open indices useful, and how is earliest-start tie-breaking maintained?
- Give a case where counting only distinct requirements produces the wrong answer.
- Why are there at most O(n) total left-pointer moves even though shrink is nested?

## CS61B and future review

- Connect the two-pointer window with HashMap load-factor intuition.
- Name a different problem where `missing` is the wrong window statistic.
- One bug I want to catch next time:

