# Attempt — Oldest Unique Event in a Live Feed

Fill this in **before** opening reference/.

- Start / finish / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- My baseline and its runtime:
- My optimized runtime and space:
- First failing test, API I forgot, or hint used:
- One issue to revisit in 2–4 days:

## Recognition and invariant

- Why does a mere HashSet not suffice once an ID becomes duplicated?
- Why must the answer reflect **first arrival**, not the smallest numeric ID?
- What do frequency[id] and firstArrivals each represent?
- Why enqueue an ID only when its count becomes 1?
- Why may the queue contain stale duplicate IDs internally but not at its head after cleanup?
- Why does a while loop inside a for loop not imply quadratic time here?
- How many total successful removals can occur over the entire run?
- What is the correct result for an empty input or a prefix with no unique IDs?

## CS61B and Java transfer

- Write the ArrayDeque methods for append, peek front, and remove front.
- Explain how getOrDefault, put, and hashing work.
- Compare amortized queue cleanup to amortized resizing of an array-backed list.

