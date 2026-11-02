# Attempt — Prefix Counts in a Routing Directory

Complete before opening `reference/`.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition and baseline
- What in the prompt suggests a trie instead of a hash set?
- What is the runtime of scanning every route for each prefix?
- What would a sorted-array + binary-search alternative cost?

## Trie invariant
- What does each node's count mean **after** processing k routes?
- Why must the root count include empty routes?
- Why do duplicate routes increment counts multiple times?
- How do you distinguish a missing child from a valid count of zero?

## Python / CS61B
- Complexity in total route characters S and total query characters Q:
- Why is `dict.setdefault` useful? How could it conceal a bug?
- Which CS61B topics connect tries, hashing, and prefix queries?
- Failed tests, hints, and one thing to remember:
