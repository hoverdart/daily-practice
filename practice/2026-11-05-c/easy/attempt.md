# Attempt — Stable Triage of a Linked Queue

Complete before opening reference/.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute-force runtime and auxiliary space:
- Optimal runtime and auxiliary space:

## Recognition and invariants

- Why is this a stable linked-list partition, not a value sort?
- What does each dummy head point to? What does its tail point to?
- Why must I save the original next pointer *before* relinking?
- Why should I detach a moved node by setting next to NULL?
- Can I explain what happens for NULL, one node, all healthy, all faulty, and duplicates?
- Do I preserve actual node identities as well as their values?
- Is the returned tail guaranteed to be NULL?

## C and CS61B reflection

- Where do C pointers and CS61B sentinel nodes meet in this solution?
- One bug or edge case that failed:
- One concept to revisit in 2–4 days:

