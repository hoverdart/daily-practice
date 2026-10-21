# Attempt — Merge Two Calibrated Chains

Fill this out **before** reading `reference/`.

- Start / finish / minutes:
- Outcome (independent / hints / reference / unfinished):
- Confidence (1–5):

## Recognition and baseline
- Why is this a two-pointer *linked-list* merge rather than a sorting problem?
- What would an array-copy + sort approach cost and violate?

## Pointer invariant
- What is the meaning of `tail` after each iteration?
- Which original nodes are already in the merged prefix?
- Why save or advance the chosen head before changing `tail->next`?
- Why must equal values choose list `a`?

## Complexity
- Time / auxiliary space:
- Why is recursion a poor choice for 200,000 nodes?

## Mistakes, failed cases, hints, C++ syntax
- Dummy sentinel / `nullptr` / `->` / ownership:

## After reference
- One invariant to remember:
- One CS61B connection:
